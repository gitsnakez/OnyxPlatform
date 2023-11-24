using System;
using System.Security.Cryptography;
using System.Windows.Interop;

namespace Onyx
{
    static public class Engine
    {
        static public IntPtr WindowHandle = IntPtr.Zero;
        static public void OnCreate()
        {
            MessageWindow.Show(WindowHandle, "Wha", "Some text");
        }

        static public void OnUpdate()
        {

        }

        static public void OnDestroy()
        {

        }

        static public void OnResizeWindow()
        {

        }

        static public void OnChangeWindowPosition()
        {

        }

        static public void OnEnter()
        {

        }

        static public void OnLeave()
        {

        }

        static public void OnKeyDown(int keyCode)
        {

        }

        static public void OnKeyUp(int keyCode)
        {

        }

        static public void OnMouseMove(int X, int Y)
        {

        }

        static public void OnMouseButtonDown(bool isLeftButton, int X, int Y)
        {

        }

        static public void OnMouseButtonUp(bool isLeftButton, int X, int Y)
        {

        }
    }
}