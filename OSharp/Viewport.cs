using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace OSharp
{
    public class Viewport : IDisposable
    {
        // Not implemented c++ part and destructor
        #region Constructor/Destructor
        public Viewport()
        {
            _windowClass = CreateWindowViewport();
            _windowHandle = GetWindowHandle(_windowClass);

            // initialization...
            WindowAppearance = new DesktopWindowsManagerAppearance(_windowHandle);
        }

        public void Dispose()
        {
            ///
        }
        #endregion
        #region General properties
        public IntPtr Handle { get => _windowHandle; private set { } }
        private readonly IntPtr _windowClass;
        private readonly IntPtr _windowHandle;

        public string Title
        {
            get => _title;
            set
            {
                _title = value;
                SetWindowText(_windowHandle, _title);
            }
        }
        private string _title;

        public int Width
        {
            get => (int)(_size.Width);
            set
            {
                Size = new Size(value, _size.Height);
            }
        }
        public int Height
        {
            get => (int)(_size.Height);
            set
            {
                Size = new Size(_size.Width, value);
            }
        }
        public Size Size
        {
            get => _size;
            set
            {
                _size = value;
                _resizeWindow(_size);
            }
        }
        private Size _size;
        #endregion
        #region Appearance
        public DesktopWindowsManagerAppearance WindowAppearance { get; set; }
        #endregion
        #region Functions
        [DllImport("user32.dll")]
        private static extern void SetWindowText(IntPtr hWnd, string lpString);

        [DllImport("user32.dll")]
        private static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);

        [DllImport("user32.dll")]
        private static extern bool MoveWindow(IntPtr hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint);

        // Resize Window
        private struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }
        private void _resizeWindow(Size size)
        {
            RECT rect;

            GetWindowRect(_windowHandle, out rect);
            MoveWindow(_windowHandle, rect.Left, rect.Top, (int)size.Width, (int)size.Height, true);
        }

        [DllImport("OnyxCLR.dll")]
        private static extern IntPtr CreateWindowViewport();

        [DllImport("OnyxCLR.dll")]
        private static extern IntPtr GetWindowHandle(IntPtr winClass);

        #endregion
    }

    public enum ImmersiveWindowMode
    {
        Default = 0,
        Light = 0,
        Dark = 1
    }
    public enum ViewportCornerStyle
    {
        Default = 0,
        Rectangle = 1,
        Rounded = 2,
        SlightlyRounded = 3
    }

    public class DesktopWindowsManagerAppearance
    {
        #region Constructor
        public DesktopWindowsManagerAppearance()
        {

        }

        internal DesktopWindowsManagerAppearance(IntPtr hWnd)
        {
            _windowHandle = hWnd;
            _updateAppearanceValues();
            _updateTitleBarColors();
        }

        internal readonly IntPtr _windowHandle;
        #endregion
        #region Corner style / Dark mode
        private void _updateAppearanceValues()
        {
            // immersive dark mode
            if (DwmSetWindowAttribute(_windowHandle, 19, _immersiveMode, sizeof(int)) != 0)
                DwmSetWindowAttribute(_windowHandle, 20, _immersiveMode, sizeof(int));

            // border style
            DwmSetWindowAttribute(_windowHandle, 33, _cornerStyle, sizeof(int));
        }

        public ImmersiveWindowMode ImmersiveMode
        {
            get
            {
                return _immersiveMode;
            }
            set
            {
                _immersiveMode = value;

                if (DwmSetWindowAttribute(_windowHandle, 19, _immersiveMode, sizeof(int)) != 0)
                    DwmSetWindowAttribute(_windowHandle, 20, _immersiveMode, sizeof(int));
            }
        }
        private ImmersiveWindowMode _immersiveMode = ImmersiveWindowMode.Default;
        public ViewportCornerStyle CornerStyle
        {
            get { return _cornerStyle; }
            set
            {
                _cornerStyle = value;
                DwmSetWindowAttribute(_windowHandle, 33, _cornerStyle, sizeof(int));
            }
        }
        public ViewportCornerStyle _cornerStyle = ViewportCornerStyle.Default;
        #endregion
        #region TitleBarColors
        internal struct DWMCOLOR
        {
            internal DWMCOLOR(int attribNum, uint value)
            {
                Attribute = attribNum;
                Color = value;
            }

            internal int Attribute;
            internal uint Color;
        }

        private void _updateTitleBarColors()
        {
            DwmSetWindowAttribute(_windowHandle, _bordercolor.Attribute, _bordercolor.Color, sizeof(uint));
            DwmSetWindowAttribute(_windowHandle, _backcolor.Attribute, _backcolor.Color, sizeof(uint));
            DwmSetWindowAttribute(_windowHandle, _forecolor.Attribute, _forecolor.Color, sizeof(uint));
        }

        /// <summary>
        /// Activate properties: BorderColor, Backcolor and Forecolor
        /// </summary>
        /// <remarks>Works only on Windows 11!</remarks>
        bool UseCustomTitleBarColors
        {
            get { return _useCustomColors; }
            set { _updateTitleBarColors(); _useCustomColors = value; }
        }
        bool _useCustomColors = false;

        /// <summary>
        /// Change border color of window.
        /// </summary>
        /// <remarks>Works only on Windows 11!</remarks>
        public Color BorderColor
        {
            get { return FromHEXtoRGB(_bordercolor); }
            set { _setUintDWMColor(_bordercolor, value); }
        }
        private DWMCOLOR _bordercolor = new DWMCOLOR(34, 0xFFFFFFFF);

        /// <summary>
        /// Change titlebrush background color of window.
        /// </summary>
        /// <remarks>Works only on Windows 11!</remarks>
        public Color Backcolor
        {
            get { return FromHEXtoRGB(_backcolor); }
            set { _setUintDWMColor(_backcolor, value); }
        }
        private DWMCOLOR _backcolor = new DWMCOLOR(35, 0xFFFFFFFF);

        /// <summary>
        /// Change titlebrush text color of window.
        /// </summary>
        /// <remarks>Works only on Windows 11!</remarks>
        public Color Forecolor
        {
            get { return FromHEXtoRGB(_forecolor); }
            set { _setUintDWMColor(_forecolor, value); }
        }
        private DWMCOLOR _forecolor = new DWMCOLOR(36, 0xFFFFFFFF);
        #endregion
        #region Fuctions
        [DllImport("DwmApi")]
        private static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, object attrValue, int attrSize);
        private void _setUintDWMColor(DWMCOLOR dwmColor, Color color)
        {
            dwmColor.Color = FromRGBtoHEX(color);

            if (UseCustomTitleBarColors)
                DwmSetWindowAttribute(_windowHandle, dwmColor.Attribute, dwmColor.Color, sizeof(uint));
        }

        private uint FromRGBtoHEX(Color color)
        {
            return (uint)(((color.R & 0xff) << 24) + ((color.G & 0xff) << 16) + ((color.B & 0xff) << 8) + (color.A & 0xff));
        }

        static private Color FromHEXtoRGB(DWMCOLOR color)
        {
            return (Color)ColorConverter.ConvertFromString($"#{color.Color}");
        }
        #endregion
    }
}