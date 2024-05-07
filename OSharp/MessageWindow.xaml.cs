using OSharp.Standard;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Media;
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
    public enum ButtonTheme
    {
        Blue,
        Red
    }

    /// <summary>
    /// Логика взаимодействия для MessageWindow.xaml
    /// </summary>
    public sealed partial class MessageWindow : Window
    {
        int _type = 0;

        internal MessageWindow()
        {
            InitializeComponent();
        }

        const string appstr = "pack://application:,,,/OSharp;";

        public void ChangeButtonTheme(ButtonTheme bTheme)
        {
            ResourceDictionary rd = new ResourceDictionary() { Source = new Uri("/OSharp;component/MainStylesDictionary.xaml", UriKind.RelativeOrAbsolute) };
            ResourceDictionary thm;
            switch (bTheme)
            {
                case ButtonTheme.Blue:
                    thm = new ResourceDictionary() { Source = new Uri("/OSharp;component/FlatButton/Blue.xaml", UriKind.RelativeOrAbsolute) };
                    Resources.Clear();
                    Resources.MergedDictionaries.Add(rd);
                    Resources.MergedDictionaries.Add(thm);
                break;

                case ButtonTheme.Red:
                    thm = new ResourceDictionary() { Source = new Uri("/OSharp;component/FlatButton/Red.xaml", UriKind.RelativeOrAbsolute) };
                    Resources.Clear();
                    Resources.MergedDictionaries.Add(rd);
                    Resources.MergedDictionaries.Add(thm);
                break;
            }
        }

        public static void Show(IntPtr owner, string caption, string message, int type, string details)
        {
            var msgDial = new MessageWindow();
            if (owner != IntPtr.Zero) new WindowInteropHelper(msgDial).Owner = owner;
            msgDial.Title = caption;
            msgDial.MessageLabel.Content = message;
            if (type != 0) msgDial._type = type;

            if (details != "") { msgDial.DetailsBox.Text = details; msgDial.DetailsBox.Visibility = Visibility.Visible; msgDial.DetailsLabel.Visibility = Visibility.Visible; }
            msgDial.ShowDialog();
        }

        protected override void OnContentRendered(EventArgs e)
        {
            base.OnContentRendered(e);
            OWM.DwmSetWindowAttribute(this, DWM.ImmersiveMode.Dark);
            OWM.DwmSetWindowAttribute(this, DWM.Color.Title, Color.FromRgb(48, 48, 48));

            if(_type == 1)
                OWM.DwmSetWindowAttribute(this, DWM.Color.Border, Color.FromRgb(196, 43, 28));
            else
                OWM.DwmSetWindowAttribute(this, DWM.Color.Border, Color.FromRgb(0, 112, 226));
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (_type == 1)
            {
                ChangeButtonTheme(ButtonTheme.Red);
                PlaySound(File.OpenRead(@"C:\Windows\Media\Windows Unlock.wav"));
            }
            else
                ChangeButtonTheme(ButtonTheme.Blue);
        }

        private void PlaySound(Stream stream)
        {
            using (var s = stream)
            {
                SoundPlayer player = new SoundPlayer(s);
                player.Load();
                player.Play();
            }
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.Key == Key.Enter)
                okButton.RaiseEvent(new RoutedEventArgs(System.Windows.Controls.Primitives.ButtonBase.ClickEvent));
        }
    }
}
