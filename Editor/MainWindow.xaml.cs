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

            new Thread(()=> { EngineLoop(); }).Start();
        }

        private IntPtr _engine;
        private IntPtr _viewport;

        private void EngineLoop()
        {
            _engine = OAPI.CreateEngine();
            _viewport = OAPI.CreateViewport(_controlHost.Handle, _engine);
            OAPI.OnCreateViewport(_viewport);

            while(IsRunning)
            {
                OAPI.OnUpdateViewport(_viewport, 0.16f);
                Thread.Sleep(1);
            }

            OAPI.OnDestroyViewport(_viewport);
        }

        private ControlHost _controlHost = null;
        private bool disposed;
        

        private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
        {
            Loaded -= RibbonWindow_Loaded;
            _controlHost = new ControlHost();
            _controlHost.MessageHook += new System.Windows.Interop.HwndSourceHook(HostMessageFilter);
            viewportPlace.Content = _controlHost;
        }

        private IntPtr HostMessageFilter(IntPtr hwnd, int msg, IntPtr wparam, IntPtr lparam, ref bool handled)
        {
            switch ((OAPI.Win32Msg)msg)
            {
                case OAPI.Win32Msg.WM_SIZE: break;
                case OAPI.Win32Msg.WM_SIZING: break;
                case OAPI.Win32Msg.WM_PAINT: break;
                case OAPI.Win32Msg.WM_ENTERSIZEMOVE: break;
                case OAPI.Win32Msg.WM_EXITSIZEMOVE: break;
                    default: break;
            }

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

        private bool IsRunning = true;
        private void RibbonWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            IsRunning = false;
        }
    }
}
