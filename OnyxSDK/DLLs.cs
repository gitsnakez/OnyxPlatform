using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;

namespace OnyxSDK
{
    static public class DWM
    {
        public enum Color
        {
            Border = 34,
            Title = 35,
            Text = 36,
        }

        public enum CornerType
        {
            Rectangle = 1,
            Round = 2,
            SlightlyRound = 3
        }

        public enum ImmersiveMode
        {
            Dark = 1,
            Light = 0
        }
    }

    /// <summary>
    /// Onyx Windows Manager
    /// </summary>
    public static class OWM
    {
        private const string DLLpath = "owm.dll";

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static private extern bool SetDwmColorWindowAttribute(IntPtr Handle, int attribute, uint red, uint green, uint blue);

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static private extern bool SetDwmModeWindowAttribute(IntPtr Handle, int attribute, int value);

        static public void DwmSetWindowAttribute(Window window, DWM.Color attribute, Color value)
        {
            WindowInteropHelper wih = new WindowInteropHelper(window);

            if (!SetDwmColorWindowAttribute(wih.Handle, (int)(attribute), value.R, value.G, value.B))
                throw new ArgumentException("Something went wrong with window");
        }

        static public void DwmSetWindowAttribute(Window window, DWM.ImmersiveMode value)
        {
            WindowInteropHelper wih = new WindowInteropHelper(window);

            if (!SetDwmModeWindowAttribute(wih.Handle, 20, (int)(value)))
                throw new ArgumentException("Something went wrong with window");
        }

        static public void DwmSetWindowAttribute(Window window, DWM.CornerType value)
        {
            WindowInteropHelper wih = new WindowInteropHelper(window);

            if (!SetDwmModeWindowAttribute(wih.Handle, 33, (int)(value)))
                throw new ArgumentException("Something went wrong with window");
        }
    }

    /// <summary>
    /// Onyx Engine API
    /// </summary>
    public static class OAPI
    {
        private const string DLLpath = "oapi.dll";

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern IntPtr CreateRenderViewportWindow(IntPtr Parent);

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern IntPtr CreateRenderWindowBorderless();

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern IntPtr GetRenderWindowHandle(IntPtr viewport);

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern void StopRenderWindow(IntPtr Wnd);



        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern void InitGraphics(IntPtr windowPtr);

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern void LoopGraphics(IntPtr windowPtr);

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern int DestroyGraphics(IntPtr windowPtr);

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern int RunWithGraphics(IntPtr hWin);
    }
}