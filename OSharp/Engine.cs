using System;
using System.Runtime.Remoting.Channels;
using System.Security.Cryptography;
using System.Threading;
using System.Windows;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media.Media3D;

// Local namespaces
using OSharp.Interfaces;

namespace OSharp
{
    static public partial class Engine
    {
        #region Local types
        // Unmaneged pointers
        static public IntPtr WindowHandle = IntPtr.Zero;
        static public IntPtr ViewportHandle = IntPtr.Zero;
        static public IntPtr EngineHandle = IntPtr.Zero;

        static public IWindowCallBack CallBack;
        static public IInputSystem Input;

        // Deltatime
        internal static bool UseDelay = true;
        internal static float deltatime = 0;
        private static DateTime time1 = DateTime.Now;
        private static DateTime time2 = DateTime.Now;

        // Frames Per Second
        public static float m_secondCounter;
        public static float m_tempFps;
        public static float FPS = 0;

        // Camera
        internal static float rotx = 0;
        internal static float roty = 0;
        internal static float oldrotx = 0;
        internal static float oldroty = 0;
        internal static float camx = 0;
        internal static float camy = 0;

        // Movement
        internal static float forward = 0;
        internal static float rightward = 0;
        internal static float movespeed = 0;

        internal static bool _isPlay = false;

        //Theme appearence
        [Obsolete]
        static private bool isUseEngine = true;
        [Obsolete]
        static public bool IsDarkThemeOld = true;
        [Obsolete]
        static public bool IsDarkTheme = true;
        [Obsolete]
        static public bool IsClassicTheme = false;
        #endregion
        static public void OnCreate()
        {
            DebugMenu.Initialize();
            ConsoleWindow.Initialize();

            if (isUseEngine)
            {
                EngineHandle = CreateEngine();
                ViewportHandle = CreateViewport(WindowHandle, EngineHandle);
                OnCreateViewport(ViewportHandle);

                // Movement
                forward = 0;
                rightward = 0;

                // Camera rotation
                roty = 3;
                oldrotx = rotx;
                oldroty = roty;
                UpdateRotateParameters(ViewportHandle, rotx, roty);
            }
        }

        static public void OnUpdate()
        {
            if (isUseEngine)
            {
                time2 = DateTime.Now;
                deltatime = (time2.Ticks - time1.Ticks) / 10000000f;

                if (_isPlay)
                {
                    camx = ExtMath.Lerp(oldrotx, rotx, deltatime * 50);
                    camy = ExtMath.Lerp(oldroty, roty, deltatime * 50);
                    oldrotx = camx;
                    oldroty = camy;
                    UpdateMovementParameters(ViewportHandle, forward, rightward);
                    UpdateRotateParameters(ViewportHandle, camx, camy);
                    forward = 0;
                    rightward = 0;

                    movespeed = 1;
                }
                else
                {
                    camx = oldrotx;
                    camy = oldroty;
                }

                OnUpdateViewport(ViewportHandle, deltatime);

                if (UseDelay) Thread.Sleep(1);

                if (m_secondCounter <= 1)
                {
                    m_secondCounter += deltatime;
                    m_tempFps++;
                }
                else
                {
                    FPS = m_tempFps;    //actual fps
                    m_secondCounter = 0;
                    m_tempFps = 0;
                }

                time1 = time2;
            }
        }

        static public void OnDestroy()
        {
            if (isUseEngine)
            {
                OnDestroyViewport(ViewportHandle);
            }
        }

        static public void OnResizeWindow()
        {
            if (isUseEngine)
            {
                OnResizeViewport(ViewportHandle);
            }
        }

        static public void OnChangeWindowPosition()
        {
            if (isUseEngine)
            {
                OnResizeViewport(ViewportHandle);
            }
        }

        static public void OnEnter()
        {

        }

        static public void OnLeave()
        {
            
        }

        static bool useBorders = true;
        static bool isX = false;
        static bool isAcute = false;
        static bool keyZ = false;

        static public void OnKeyDown(int keyCode)
        {
            switch((Keyboard)keyCode)
            {
                // Maximize viewport
                case Keyboard.Enter:
                    //CallBack.ChangeWindowBorderStyles(WindowHandle, false);
                    useBorders = false;
                    SetFullscreenMode(ViewportHandle, true, 1920, 1080);
                    break;

                // Minimize viewport
                case Keyboard.Escape:
                    var size = CallBack.GetWindowSize(WindowHandle);
                    SetFullscreenMode(ViewportHandle, false, size.Width, size.Height);
                    useBorders = true;
                    //CallBack.ChangeWindowBorderStyles(WindowHandle, true);
                    break;

                // Open debug menu
                case Keyboard.X:
                    if (isX)
                        break;
                    var loc = CallBack.GetWindowLocation(WindowHandle);
                    DebugMenu.Switch(loc.X - 270, loc.Y);
                    isX = true;
                    break;

                // Open debug menu
                case Keyboard.Acute:
                    if(isAcute)
                        break;
                    ConsoleWindow.Switch();
                    isAcute = true;
                    break;

                // Fly mode
                case Keyboard.Z:
                    if (!keyZ)
                        break;

                    keyZ = true;
                    _isPlay = !_isPlay;
                    break;

                // Forward
                case Keyboard.W:
                    forward = movespeed * (deltatime * 16);
                    break;

                // Left
                case Keyboard.A:
                    rightward = -movespeed * (deltatime * 16);
                    break;

                // Back
                case Keyboard.S:
                    forward = -movespeed * (deltatime * 16);
                    break;

                // Right
                case Keyboard.D:
                    rightward = movespeed * (deltatime * 16);
                    break;
            }
        }

        static public void OnKeyUp(int keyCode)
        {
            switch ((Keyboard)keyCode)
            {
                case Keyboard.X:
                    isX = false;
                    break;

                case Keyboard.Acute:
                    isAcute = false;
                    break;

                case Keyboard.Z:
                    if (_isPlay)
                    {
                        Input.ShowCursor();
                        _isPlay = false;
                        rotx = oldrotx;
                        roty = oldroty;
                        forward = 0;
                        rightward = 0;
                    }
                    else
                    {
                        O_Size size = CallBack.GetWindowSize(WindowHandle);
                        O_Location loc = CallBack.GetWindowLocation(WindowHandle);
                        int width_center = (size.Width - (useBorders ? 16 : 0)) / 2;
                        int height_center = (size.Height - (useBorders ? 39 : 0)) / 2;
                        Input.HideCursor();
                        Input.SetCursorPosition(new O_Location(loc.X + (useBorders ? 8 : 0) + width_center, loc.Y + (useBorders ? 31 : 0) + height_center));
                        _isPlay = true;
                    }
                    break;

                // Set window theme (classic or standart)
                case Keyboard.H:
                    IsClassicTheme = !IsClassicTheme;
                    CallBack.ChangeWindowTheme(WindowHandle, IsClassicTheme);
                    break;
            }
        }

        static public void OnMouseMove(int X, int Y)
        {
            // Camera rotation
            if (_isPlay)
            {
                O_Size size = CallBack.GetWindowSize(WindowHandle);
                O_Location loc = CallBack.GetWindowLocation(WindowHandle);
                int width_center = (size.Width - (useBorders ? 16 : 0)) / 2;
                int height_center = (size.Height - (useBorders ? 39 : 0)) / 2;

                roty += ((X - (loc.X + (useBorders ?  8 : 0))) - width_center) * deltatime * 0.1f;
                rotx += ((Y - (loc.Y + (useBorders ? 31 : 0))) - height_center) * deltatime * 0.1f;

                if (rotx > 1.5f)
                    rotx = 1.5f;
                else if (rotx < -1.5f)
                    rotx = -1.5f;

                Input.SetCursorPosition(new O_Location(loc.X + (useBorders ? 8 : 0) + width_center, loc.Y + (useBorders ? 31 : 0) + height_center));
            }
        }

        static public void OnMouseButtonDown(bool isLeftButton, int X, int Y)
        {

        }

        static public void OnMouseButtonUp(bool isLeftButton, int X, int Y)
        {

        }
    }
}