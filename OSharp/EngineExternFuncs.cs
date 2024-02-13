using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OSharp
{
    static public partial class Engine
    {
        internal const string DLLpath = "bin\\Engine.dll";

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern IntPtr CreateViewport(IntPtr hWnd, IntPtr engine);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static private extern IntPtr CreateEngine();

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static private extern IntPtr ReleaseEngine(IntPtr engine);

        // Event methods

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void OnCreateViewport(IntPtr vp);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void OnUpdateViewport(IntPtr vp, float deltaTime);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void OnResizeViewport(IntPtr vp);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void OnDestroyViewport(IntPtr vp);

        // Other

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void ResizeViewport(IntPtr vp, int width, int heigth);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void UpdateRotateParameters(IntPtr vp, float camx, float camy);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void UpdateMovementParameters(IntPtr vp, float forward, float rightward);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void NormalizeEngine(IntPtr vp, bool isnormal);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void SetSensitivity(IntPtr vp, float sens);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void ReloadMap(IntPtr vp);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void ReloadMaterials(IntPtr vp);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void SetVSync(IntPtr vp, bool vsync);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void UpdateMeshInfo(IntPtr mesh, bool isrender, float[] transform);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern float GetOldX(IntPtr vp);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern float GetOldY(IntPtr vp);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern void SetFullscreenMode(IntPtr vp, bool isFullScr, int winWidth, int winHeight);

        [DllImport(DLLpath, CallingConvention = CallingConvention.StdCall)]
        static extern int CheckDLL();
    }
}
