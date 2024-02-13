using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;

namespace OSharp
{
    static internal class WinAppHelper
    {
        [DllImport("DwmApi")]
        private static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, ref uint attrValue, int attrSize);

        [DllImport("DwmApi")]
        private static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, ref int attrValue, int attrSize);

        internal static void SetWindowTitleBrushDark(Window window)
        {
            var winHandle = new WindowInteropHelper(window).Handle;
            uint darkmode = 1;
            if (DwmSetWindowAttribute(winHandle, 19, ref darkmode, 4) != 0)
                DwmSetWindowAttribute(winHandle, 20, ref darkmode, 4);
        }
        static int GetHex(Color color)
        {
            return ((int)(byte)(color.R) | ((int)(byte)(color.G)) << 8) | ((int)((byte)(color.B)) << 16);
        }

        internal static void SetWindowDWMColors(Window window, Color border, Color caption, Color text)
        {
            Color nullColor = Color.FromArgb(0, 0, 0, 0);

            if (border == nullColor && caption == nullColor && text == nullColor)
                return;

            var winHandle = new WindowInteropHelper(window).Handle;

            int bordercolor;
            int captioncolor;
            int textcolor;

            if (border != nullColor)
            {
                bordercolor = GetHex(border);
                DwmSetWindowAttribute(winHandle, 34, ref bordercolor, sizeof(uint));
            }

            if (caption != nullColor)
            {
                captioncolor = GetHex(caption);
                DwmSetWindowAttribute(winHandle, 35, ref captioncolor, sizeof(uint));
            }

            if (text != nullColor)
            {
                textcolor = GetHex(text);
                DwmSetWindowAttribute(winHandle, 36, ref textcolor, sizeof(uint));
            }
        }

        internal static void SetWindowDWMColors(Window window, int border, int caption, int text)
        {
            uint nullColor = 0x00000000;

            if (border == nullColor && caption == nullColor && text == nullColor)
                return;

            var winHandle = new WindowInteropHelper(window).Handle;

            if (border != nullColor)
            {
                DwmSetWindowAttribute(winHandle, 34, ref border, sizeof(uint));
            }

            if (caption != nullColor)
            {
                DwmSetWindowAttribute(winHandle, 35, ref caption, sizeof(uint));
            }

            if (text != nullColor)
            {
                DwmSetWindowAttribute(winHandle, 36, ref text, sizeof(uint));
            }
        }

        internal static void SetRectWindowBorder(Window window)
        {
            var winHandle = new WindowInteropHelper(window).Handle;
            uint corner = 1;
            DwmSetWindowAttribute(winHandle, 33, ref corner, sizeof(uint));
        }
    }
}
