using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OnyxApplication
{
    public enum Input
    {
        LeftMouseButton,
        RightMouseButton,
    }

    public struct Point
    {
        private int _x;
        private int _y;

        public int X { get => _x; set => _x = value; }
        public int Y { get => _y; set => _y = value; }

        public Point(int x, int y)
        {
            _x = x;
            _y = y;
        }
    }

    static public class App
    {
        static public void SendInput(Input input)
        {

        }
        static public void SendInput(Point location)
        {

        }

        static public void SendInput(Input input, Point location)
        {

        }
    }
}
