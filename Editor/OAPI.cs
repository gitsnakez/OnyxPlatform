using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    internal enum WindowMessage
    {
        Size = 0x0005,
        Sizing = 0x0214,
        EnterSizeMove = 0x0231,
        Paint = 0x000F,
        ExitSizeMove = 0x0232,
        SysCommand = 0x0112
    }

    internal static class OAPI
    {
        #region ENGINE
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
        #endregion
        #region OAPI
        const string oapidll = "oapi.dll";

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern IntPtr CreateRenderWindow(IntPtr Parent);

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern IntPtr CreateRenderWindowBorders();

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern IntPtr GetRenderWindowHandle(IntPtr viewport);

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern void StopRenderWindow(IntPtr viewport);

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern int RunWithGraphics(IntPtr windowPtr);

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern int RunWithGraphics2(IntPtr Parent, IntPtr viewport_pointer);



        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern void CreateGraphics(IntPtr windowPtr);

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern void UpdateGraphics(IntPtr windowPtr);

        [DllImport(oapidll, CallingConvention = CallingConvention.Cdecl)]
        static internal extern void DestroyGraphics();

        #endregion
        #region OWM
        const string owmdll = "owm.dll";
        #endregion
    }
}
