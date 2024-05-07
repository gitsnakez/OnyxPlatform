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
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace OnyxSDK
{
    /// <summary>
    /// Логика взаимодействия для MaterialTool.xaml
    /// </summary>
    public partial class MaterialTool : UserControl
    {
        public MaterialTool()
        {
            InitializeComponent();
        }

        IntPtr hWin = IntPtr.Zero;

        protected override void OnInitialized(EventArgs e)
        {
            base.OnInitialized(e);

            App.hWin = EngineHoster.Handle;

            hWin = OAPI.CreateRenderWindowBorderless();
            OAPI.InitGraphics(hWin);
            CompositionTarget.Rendering += EngineRenderLoop;
        }

        private void EngineRenderLoop(object sender, EventArgs e)
        {
            OAPI.LoopGraphics(hWin);
        }

        private void UserControl_Unloaded(object sender, RoutedEventArgs e)
        {
            OAPI.StopRenderWindow(hWin);
            OAPI.DestroyGraphics(hWin);
        }
    }
}
