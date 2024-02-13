using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace OSharp.Interfaces
{
    public struct O_Size
    {
        public O_Size(int Width, int Height)
        {
            this.Width = Width;
            this.Height = Height;
        }

        public int Width {  get; set; }
        public int Height { get; set; }
    }

    public struct O_Location
    {
        public O_Location(int X, int Y)
        {
            this.X = X;
            this.Y = Y;
        }

        public int X { get; set; }
        public int Y { get; set; }
    }

    public interface IWindowCallBack
    {
        void ChangeWindowBorderStyles(IntPtr winHandle, bool showBorders);
        void ChangeWindowTheme(IntPtr winHandle, bool isClassic);
        O_Location GetWindowLocation(IntPtr winHandle);
        O_Size GetWindowSize(IntPtr winHandle);
    }
}