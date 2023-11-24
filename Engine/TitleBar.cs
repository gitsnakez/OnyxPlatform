using System;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;

namespace Onyx
{
    static internal class TitleBar
    {
        [DllImport("DwmApi")]
        private static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, ref uint attrValue, int attrSize);

        internal static void SetWindowTitleBrushDark(Window window)
        {
            var winHandle = new WindowInteropHelper(window).Handle;
            uint darkmode = 1;
            if (DwmSetWindowAttribute(winHandle, 19, ref darkmode, 4) != 0)
                DwmSetWindowAttribute(winHandle, 20, ref darkmode, 4);
        }

        internal static void SetWindowDWMColors(Window window, Color border, Color caption, Color text)
        {
            var winHandle = new WindowInteropHelper(window).Handle;

            uint bordercolor = Convert.ToUInt32(border.ToString().Replace("#FF", "0x00"), 16);
            uint captioncolor = Convert.ToUInt32(caption.ToString().Replace("#FF", "0x00"), 16);
            uint textcolor = Convert.ToUInt32(text.ToString().Replace("#FF", "0x00"), 16);

            DwmSetWindowAttribute(winHandle, 34, ref bordercolor , sizeof(uint));
            DwmSetWindowAttribute(winHandle, 35, ref captioncolor, sizeof(uint));
            DwmSetWindowAttribute(winHandle, 36, ref textcolor, sizeof(uint));
        }

        internal static void SetRectWindowBorder(Window window)
        {
            var winHandle = new WindowInteropHelper(window).Handle;
            uint corner = 1;
            DwmSetWindowAttribute(winHandle, 33, ref corner, sizeof(uint));
        }
    }
}
