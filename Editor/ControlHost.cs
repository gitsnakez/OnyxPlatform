using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace Editor
{
    internal class ControlHost : HwndHost
    {
        public IntPtr _hwnd;

        internal ControlHost()
        {
            _hwnd = IntPtr.Zero;
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            handled = false;
            return IntPtr.Zero;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            _hwnd = OAPI.InitWin32Viewport(hwndParent.Handle, (int)Width, (int)Height);
            Debug.Assert(_hwnd != IntPtr.Zero);
            return new HandleRef(this, _hwnd);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            _hwnd = IntPtr.Zero;
        }
    }
}