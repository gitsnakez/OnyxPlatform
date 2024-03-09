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
using System.Windows.Shapes;

namespace Editor
{
    /// <summary>
    /// Interaction logic for EditorWindow.xaml
    /// </summary>
    public partial class EditorWindow : Window
    {
        public EditorWindow()
        {
            InitializeComponent();
        }

        IntPtr pViewport = IntPtr.Zero;
        IntPtr pViewportWindow = IntPtr.Zero;

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            pViewport = OAPI.CreateRenderWindow(ViewportSurface.Handle);
            pViewportWindow = OAPI.GetRenderWindowHandle(pViewport);
            new Thread(StartEngine).Start();
        }

        void StartEngine()
        {
            OAPI.RunWithGraphics(pViewport);
        }
    }
}
