using Fluent;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Editor
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : RibbonWindow
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void RibbonWindow_ContentRendered(object sender, EventArgs e)
        {
            CornerPreference = ControlzEx.Behaviors.WindowCornerPreference.DoNotRound;
            WindowState = WindowState.Maximized;

            new Thread(StartEngine).Start();
        }

        private ControlHost _controlHost = null;
        private bool disposed;

        private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
        {
            _controlHost = new ControlHost();
            //_controlHost.MessageHook += new HwndSourceHook(HostMessageFilter);
            viewportPlace.Content = _controlHost;
        }

        void StartEngine()
        {
            //IntPtr intPtr = OAPI.CreateRenderWindowBorders();
            OAPI.RunWithGraphics(_controlHost._hwndVp);
            //OAPI.UpdateGraphics(_controlHost._hwndVp);
        }

        private IntPtr HostMessageFilter(IntPtr hwnd, int msg, IntPtr wparam, IntPtr lparam, ref bool handled)
        {
            switch ((WindowMessage)msg)
            {
                case WindowMessage.Size: break;
                case WindowMessage.Sizing: break;
                case WindowMessage.Paint: break;
                case WindowMessage.EnterSizeMove: break;
                case WindowMessage.ExitSizeMove: break;
                    default: break;
            }

            /*if (inited)
                OAPI.UpdateGraphics(_controlHost._hwndVp);*/

            return IntPtr.Zero;
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposed)
            {
                if (disposing)
                    _controlHost.Dispose();

                disposed = true;
            }
        }

        public void Dispose()
        {
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }

        private void RibbonWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //OAPI.StopRenderWindow(_controlHost._hwndVp);
            //OAPI.DestroyGraphics();
        }
    }
}
