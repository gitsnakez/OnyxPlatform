using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;

namespace OSharp
{
    static internal class DebugMenu
    {
        static private OnyxMenu _debugMenu;
        static private bool _isVisible = false;
        static private OnyxMenuButton[] _buttons =
        {
            new OnyxMenuButton("GPI",       "Show GPI",        OnyxMenuButton.DefaultClickEvent),
            new OnyxMenuButton("MSG_TEST",  "Message Test",    DebugClickEvent),
            new OnyxMenuButton("CONSOLE",   "Console",         DebugClickEvent),
            new OnyxMenuButton("EDITOR",    "Open Editor",     DebugClickEvent),
            new OnyxMenuButton("QUIT",      "Quit",            OnyxMenuButton.DefaultClickEvent),
        };

        private static void DebugClickEvent(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case OnyxMenu.ButtonNameConstant + "MSG_TEST":
                    MessageWindow.Show(Engine.WindowHandle, "Test title", "Test message text");
                    break;

                case OnyxMenu.ButtonNameConstant + "CONSOLE":
                    ConsoleWindow.Switch();
                    break;

                case OnyxMenu.ButtonNameConstant + "EDITOR":
                    //Main.OpenEditor();
                    break;
            }
        }

        static internal void Initialize()
        {
            _debugMenu = new OnyxMenu("Debug menu", _buttons);
            _debugMenu.Closing += Closing;
        }

        private static void Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            _debugMenu.Hide();
            _isVisible = false;
        }

        static internal void Show()
        {
            _debugMenu?.Show();
            _isVisible = true;
        }

        static internal void Hide()
        {
            _debugMenu?.Hide();
            _isVisible = false;
        }

        static internal void Switch()
        {
            if (_isVisible)
            {
                _debugMenu?.Hide();
                _isVisible = false;
            }
            else
            {
                _debugMenu?.Show();
                _isVisible = true;
            }
        }

        static internal void Switch(int X, int Y)
        {
            if (_isVisible)
            {
                _debugMenu?.Hide();
                _isVisible = false;
            }
            else
            {
                _debugMenu?.Show();
                _debugMenu.Left = X;
                _debugMenu.Top = Y;
                _isVisible = true;
            }
        }
    }
}