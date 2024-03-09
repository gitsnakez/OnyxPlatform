using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;

namespace Editor
{
    internal class ControlHost : HwndHost
    {
        public IntPtr _hwndVp;
        public IntPtr _hwnd;

        internal ControlHost()
        {
            _hwndVp = IntPtr.Zero;
            _hwnd = IntPtr.Zero;
        }

        /*protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            handled = false;
            return IntPtr.Zero;
        }*/

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            _hwndVp = OAPI.CreateRenderWindow(hwndParent.Handle);
            _hwnd = OAPI.GetRenderWindowHandle(_hwndVp);
            Debug.Assert(_hwndVp != IntPtr.Zero, "Editor didn't get 3D viewport handler!");
            Debug.Assert(_hwnd != IntPtr.Zero, "Editor didn't get 3D viewport window handler!");
            return new HandleRef(this, _hwnd);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            _hwnd = IntPtr.Zero;
            _hwndVp = IntPtr.Zero;
        }
    }
}