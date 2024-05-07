using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace OnyxSDK
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            OWM.DwmSetWindowAttribute(this, DWM.Color.Title, Color.FromRgb(48, 48, 48));
            //OWM.DwmSetWindowAttribute(this, DWM.ImmersiveMode.Dark);
            //OWM.DwmSetWindowAttribute(this, DWM.CornerType.Rectangle);
        }

        private void StartTool(string toolpath)
        {
            if(!File.Exists(toolpath))
            {
                MessageBox.Show(this, $"bin/{toolpath} - tool not found!", "Onyx SDK", MessageBoxButton.OK);
                return;
            }

            Process.Start($"bin/{toolpath}");
        }

        private void SpriteFontToolMenuItem_Click(object sender, RoutedEventArgs e)
        {
            StartTool("SpriteFontTool.exe");
        }
    }
}
