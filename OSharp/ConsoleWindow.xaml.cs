using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace OSharp
{
    /// <summary>
    /// Логика взаимодействия для Console.xaml
    /// </summary>
    public partial class ConsoleWindow : Window
    {
        static private ConsoleWindow _consoleWindow;
        static private bool _isVisible = false;
        private ConsoleWindow(string title)
        {
            InitializeComponent();
            Title = title;
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            WindowInteropHelper wih = new WindowInteropHelper(this);
            wih.Owner = Engine.WindowHandle;
            IconHelper.RemoveIcon(this);
            WinAppHelper.SetWindowDWMColors(this, Color.FromArgb(0, 0, 0, 0), Color.FromRgb(32, 32, 32), Colors.White);
        }
        static internal void Initialize()
        {
            _consoleWindow = new ConsoleWindow("Console");
            _consoleWindow.Closing += ClosingEvent;
        }

        private static void ClosingEvent(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            _consoleWindow.Hide();
            _isVisible = false;
        }

        static internal void Switch()
        {
            if (_isVisible)
            {
                _consoleWindow?.Hide();
                _isVisible = false;
            }
            else
            {
                _consoleWindow?.Show();
                _isVisible = true;
            }
        }

        static internal void Switch(int X, int Y)
        {
            if (_isVisible)
            {
                _consoleWindow?.Hide();
                _isVisible = false;
            }
            else
            {
                _consoleWindow?.Show();
                _consoleWindow.Left = X;
                _consoleWindow.Top = Y;
                _isVisible = true;
            }
        }
    }
}
