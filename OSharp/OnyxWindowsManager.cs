using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;

namespace OSharp
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

        [DllImport(DLLpath, CallingConvention = CallingConvention.Cdecl)]
        static public extern void SetClassicWindowCaption(IntPtr Handle, bool switcher);

        static public void DwmSetWindowAttribute(Window window, DWM.Color attribute, Color value)
        {
            WindowInteropHelper wih = new WindowInteropHelper(window);

            if (!SetDwmColorWindowAttribute(wih.Handle, (int)(attribute), value.R, value.G, value.B))
                throw new ArgumentException("Something went wrong with window");
        }

        static public void DwmSetWindowAttribute(IntPtr hWnd, DWM.Color attribute, Color value)
        {
            if (!SetDwmColorWindowAttribute(hWnd, (int)(attribute), value.R, value.G, value.B))
                throw new ArgumentException("Something went wrong with window");
        }

        static public void DwmSetWindowAttribute(Window window, DWM.ImmersiveMode value)
        {
            WindowInteropHelper wih = new WindowInteropHelper(window);

            if (!SetDwmModeWindowAttribute(wih.Handle, 20, (int)(value)))
                throw new ArgumentException("Something went wrong with window");
        }

        static public void DwmSetWindowAttribute(IntPtr hWnd, DWM.ImmersiveMode value)
        {
            if (!SetDwmModeWindowAttribute(hWnd, 20, (int)(value)))
                throw new ArgumentException("Something went wrong with window");
        }

        static public void DwmSetWindowAttribute(Window window, DWM.CornerType value)
        {
            WindowInteropHelper wih = new WindowInteropHelper(window);

            if (!SetDwmModeWindowAttribute(wih.Handle, 33, (int)(value)))
                throw new ArgumentException("Something went wrong with window");
        }

        static public void DwmSetWindowAttribute(IntPtr hWnd, DWM.CornerType value)
        {
            if (!SetDwmModeWindowAttribute(hWnd, 33, (int)(value)))
                throw new ArgumentException("Something went wrong with window");
        }
    }
}