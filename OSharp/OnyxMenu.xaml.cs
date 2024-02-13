using System;
using System.Collections.Generic;
using System.Drawing;
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
    public struct OnyxMenuButton
    {
        public OnyxMenuButton(string title, RoutedEventHandler action)
        {
            Name = title;
            Title = title;
            Enabled = true;
            Action = action;
        }

        public OnyxMenuButton(string name, string title, RoutedEventHandler action)
        {
            Name = name;
            Title = title;
            Enabled = true;
            Action = action;
        }

        public OnyxMenuButton(string name, string title, bool enabled, RoutedEventHandler action)
        {
            Name = name;
            Title = title;
            Enabled = enabled;
            Action = action;
        }

        public string Name {  get; set; }
        public string Title {  get; set; }
        public bool Enabled { get; set; }
        public RoutedEventHandler Action { get; set; }

        public static void DefaultClickEvent(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case OnyxMenu.ButtonNameConstant + "GPI":
                    new GPI().Show();
                    break;

                case OnyxMenu.ButtonNameConstant + "QUIT":
                    Environment.Exit(0);
                    break;
            }
        }
    }

    /// <summary>
    /// Логика взаимодействия для DebugMenu.xaml
    /// </summary>
    public partial class OnyxMenu : Window
    {
        public const string ButtonNameConstant = "M_BTN_";
        public void AddButton(OnyxMenuButton Button)
        {
            Button newBtn = new Button();

            newBtn.Content = Button.Title;
            newBtn.Name = ButtonNameConstant + Button.Name;
            newBtn.IsEnabled = Button.Enabled;
            newBtn.Click += Button.Action;

            ButtonContainer.Children.Add(newBtn);
        }

        public OnyxMenu(OnyxMenuButton[] MenuButtons)
        {
            InitializeComponent();

            Init(MenuButtons);
        }

        public OnyxMenu(string MenuTitle, OnyxMenuButton[] MenuButtons)
        {
            InitializeComponent();
            Title = MenuTitle;
            Init(MenuButtons);
        }

        private void Init(OnyxMenuButton[] MenuButtons)
        {
            for (int i = 0; i < MenuButtons.Length; i++)
            {
                AddButton(MenuButtons[i]);
            }

            if (MenuButtons.Length < 3)
            {
                ButtonContainer.MaxHeight = 30;
                MaxHeight = 30 + 47;
            }
            else
            {
                int targetHeight = (ButtonContainer.Children.Count / 2) * 30;
                if (ButtonContainer.Children.Count % 2 == 1) targetHeight += 30;

                ButtonContainer.MaxHeight = targetHeight;
                MaxHeight = targetHeight + 47;
            }
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            WindowInteropHelper wih = new WindowInteropHelper(this);
            wih.Owner = Engine.WindowHandle;
            IconHelper.RemoveIcon(this);
            WinAppHelper.SetWindowDWMColors(this, Color.FromArgb(0,0,0,0), Color.FromRgb(32, 32, 32), Colors.White);
        }
    }
}
