using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OSharp.InputSystem
{
    #region Input System Enums
    /// <summary>
    /// Storage of signs of all keyboard keys
    /// </summary>
    public enum Keyboard
    {
        Backspace = 0x08,
        Tab = 0x09,
        //Clear = 0x0C,
        Enter = 0x0D,
        Shift = 0x10,
        Control = 0x11,
        Alt = 0x12,
        Pause = 0x13,
        CapsLock = 0x14,
        Escape = 0x1B,
        Space = 0x20,
        PageUp = 0x21,
        PageDown = 0x22,
        End = 0x23,
        Home = 0x24,
        LeftArrow = 0x25,
        UpArrow = 0x26,
        RightArrow = 0x27,
        DownArrow = 0x28,
        Select = 0x29,
        Print = 0x2A,
        Execute = 0x2B,
        PrintScreen = 0x2C,
        Insert = 0x2D,
        Delete = 0x2E,
        Help = 0x2F,

        Key0 = 0x30,
        Key1 = 0x31,
        Key2 = 0x32,
        Key3 = 0x33,
        Key4 = 0x34,
        Key5 = 0x35,
        Key6 = 0x36,
        Key7 = 0x37,
        Key8 = 0x38,
        Key9 = 0x39,

        Q = 0x51,
        W = 0x57,
        E = 0x45,
        R = 0x52,
        T = 0x54,
        Y = 0x59,
        U = 0x55,
        I = 0x49,
        O = 0x4F,
        P = 0x50,
        A = 0x41,
        S = 0x53,
        D = 0x44,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        Z = 0x5A,
        X = 0x58,
        C = 0x43,
        V = 0x56,
        B = 0x42,
        N = 0x4E,
        M = 0x4D,

        LeftWin = 0x5B,
        RightWin = 0x5C,
        Apps = 0x5D,
        /// <summary>
        /// Computer sleep key
        /// </summary>
        Sleep = 0x5F,

        Num0 = 0x60,
        Num1 = 0x61,
        Num2 = 0x62,
        Num3 = 0x63,
        Num4 = 0x64,
        Num5 = 0x65,
        Num6 = 0x66,
        Num7 = 0x67,
        Num8 = 0x68,
        Num9 = 0x69,

        /// <summary>
        /// *
        /// </summary>
        Multiply = 0x6A,
        /// <summary>
        /// +
        /// </summary>
        Add = 0x6B,
        //Separator = 0x6C,
        /// <summary>
        /// -
        /// </summary>
        Subtract = 0x6D,
        /// <summary>
        /// . or ,
        /// </summary>
        Decimal = 0x6E,
        /// <summary>
        /// /
        /// </summary>
        Divide = 0x6F,

        F1 = 0x70,
        F2 = 0x71,
        F3 = 0x72,
        F4 = 0x73,
        F5 = 0x74,
        F6 = 0x75,
        F7 = 0x76,
        F8 = 0x77,
        F9 = 0x78,
        F10 = 0x79,
        F11 = 0x7A,
        F12 = 0x7B,
        //F13 = 0x7C,
        //F14 = 0x7D,
        //F15 = 0x7E,
        //F16 = 0x7F,
        //F17 = 0x80,
        //F18 = 0x81,
        //F19 = 0x82,
        //F20 = 0x83,
        //F21 = 0x84,
        //F22 = 0x85,
        //F23 = 0x86,
        //F24 = 0x87,

        NumLock = 0x90,
        ScrollLock = 0x91,
        LeftShift = 0xA0,
        RightShift = 0xA1,
        LeftControl = 0xA2,
        RightControl = 0xA3,
        LeftAlt = 0xA4,
        RightAlt = 0xA5,

        /// <summary>
        /// ` or ~
        /// </summary>
        Acute = 0xC0,
        /// <summary>
        /// -
        /// </summary>
        Dash = 0xBD,
        /// <summary>
        /// \ |
        /// </summary>
        Slash2 = 0xE2,
        /// <summary>
        /// \ |
        /// </summary>
        Slash1 = 0xDC,
        /// <summary>
        /// + =
        /// </summary>
        Plus = 0xBB,
        /// <summary>
        /// ,
        /// </summary>
        Comma = 0xBC,
        /// <summary>
        /// -
        /// </summary>
        Minus = 0xBD,
        /// <summary>
        /// .
        /// </summary>
        Period = 0xBE,
        /// <summary>
        /// ? /
        /// </summary>
        QuestionMark = 0xBF,
        /// <summary>
        /// Open Square Bracket [ {
        /// </summary>
        OSB = 0xDB,
        /// <summary>
        /// Close Square Bracket ] }
        /// </summary>
        CSB = 0xDD,
        /// <summary>
        /// "
        /// </summary>
        Quote = 0xDE,
    }

    /// <summary>
    /// Storage of mouse keys, buttons
    /// </summary>
    public enum Mouse
    {
        LeftMouseButton = 0x01,
        RightMouseButton = 0x02,
        MouseWheel = 0x04,
        MouseButton4 = 0x05,
        MouseButton5 = 0x06,
    }
    #endregion

    public struct Point
    {
        int X;
        int Y;
    }

    public interface IViewportInputCallback
    {
        void OnKeyDown(int key);
        void OnKeyUp(int key);

        void OnMouseMove(Point DeltaMousePosition);
		void OnMouseLeftButtonDown(Point delta_mouse_pos);
		void OnMouseLeftButtonUp(Point delta_mouse_pos);
		void OnMouseRightButtonDown(Point delta_mouse_pos);
		void OnMouseRightButtonUp(Point delta_mouse_pos);
    }
}