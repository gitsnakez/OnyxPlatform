using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
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
    /// Логика взаимодействия для LoginWindow.xaml
    /// </summary>
    public partial class MessageWindow : Window
    {
        public IntPtr ParentHWND = IntPtr.Zero;
        public MessageWindow(string title, string message)
        {
            InitializeComponent();
            Title = title;
            Message.Content = message;
        }

        public static bool? Show(IntPtr Parent, string title, string message)
        {
            var dialog = new MessageWindow(title, message);
            WindowInteropHelper wih = new WindowInteropHelper(dialog);
            wih.Owner = Parent;
            dialog.ParentHWND = Parent;
            return dialog.ShowDialog();
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            IconHelper.RemoveIcon(this);
            WinAppHelper.SetWindowTitleBrushDark(this);
            WinAppHelper.SetWindowDWMColors(this, Color.FromArgb(255, 52, 52, 52), Color.FromArgb(255, 38, 38, 38), Colors.White);
            //TitleBar.SetRectWindowBorder(this);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
