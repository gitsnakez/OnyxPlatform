using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    internal static class OAPI
    {
        internal enum Win32Msg
        {
            WM_SIZE = 0x0005,
            WM_SIZING = 0x0214,
            WM_ENTERSIZEMOVE = 0x0231,
            WM_PAINT = 0x000F,
            WM_EXITSIZEMOVE = 0x0232
        }

        const string oapidll = "oapi.dll";
        const string owmdll = "owm.dll";
        const string enginedll = "Engine.dll";

        [DllImport(enginedll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern IntPtr CreateEngine();

        [DllImport(enginedll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern IntPtr CreateViewport(IntPtr hWnd, IntPtr engine);

        [DllImport(enginedll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern IntPtr OnCreateViewport(IntPtr viewport);

        [DllImport(enginedll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern void OnUpdateViewport(IntPtr vp, float deltaTime);

        [DllImport(enginedll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern void OnDestroyViewport(IntPtr vp);

        [DllImport(enginedll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern void OnResizeViewport(IntPtr vp);



        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern IntPtr InitWin32Viewport(IntPtr Parent, int Width, int Height);
    }
}
