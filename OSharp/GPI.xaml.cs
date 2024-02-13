using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data.Common;
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
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Xml.Linq;

namespace OSharp
{
    /// <summary>
    /// Логика взаимодействия для GPI.xaml
    /// </summary>
    public partial class GPI : Window
    {
        DispatcherTimer dispatcherTimer = new DispatcherTimer();
        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            DataItemList[0].Value = Engine.FPS.ToString();
            DataItemList[1].Value = Engine.deltatime.ToString();
        }

        public GPI()
        {
            InitializeComponent();
        }

        public class DataItem : INotifyPropertyChanged
        {
            private string _name;
            public string Name
            {
                get { return _name; }
                set
                {
                    if (_name != value)
                    {
                        _name = value;
                        OnPropertyChanged("Name");
                    }
                }
            }

            private string _value;
            public string Value
            {
                get { return _value; }
                set
                {
                    if (_value != value)
                    {
                        _value = value;
                        OnPropertyChanged("Value");
                    }
                }
            }

            public event PropertyChangedEventHandler PropertyChanged;

            private void OnPropertyChanged(string propertyName)
            {
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        public ObservableCollection<DataItem> DataItemList { get; set; }

        protected override void OnSourceInitialized(EventArgs e)
        {
            WindowInteropHelper wih = new WindowInteropHelper(this);
            wih.Owner = Engine.WindowHandle;
            IconHelper.RemoveIcon(this);
            WinAppHelper.SetWindowDWMColors(this, Color.FromArgb(0, 0, 0, 0), Color.FromRgb(32, 32, 32), Colors.White);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            DataItemList = new ObservableCollection<DataItem>()
            {
                new DataItem { Name = "fps", Value = Engine.FPS.ToString() },
                new DataItem { Name = "delta time", Value = Engine.deltatime.ToString() }
            };
            GPI_Table.ItemsSource = DataItemList;
            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 1);
            dispatcherTimer.Start();
        }
    }
}
