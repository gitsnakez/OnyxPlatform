using System;
using System.Runtime.InteropServices;

namespace OnyxPlatform
{
    static internal class TitleBar
    {
        [DllImport("DwmApi")]
        public static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, int[] attrValue, int attrSize);
    }
}