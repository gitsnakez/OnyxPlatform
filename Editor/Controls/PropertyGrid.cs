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

namespace Editor.Controls
{
    /// <summary>
    /// Выполните шаги 1a или 1b, а затем 2, чтобы использовать этот пользовательский элемент управления в файле XAML.
    ///
    /// Шаг 1a. Использование пользовательского элемента управления в файле XAML, существующем в текущем проекте.
    /// Добавьте атрибут XmlNamespace в корневой элемент файла разметки, где он 
    /// будет использоваться:
    ///
    ///     xmlns:MyNamespace="clr-namespace:Editor.Controls"
    ///
    ///
    /// Шаг 1б. Использование пользовательского элемента управления в файле XAML, существующем в другом проекте.
    /// Добавьте атрибут XmlNamespace в корневой элемент файла разметки, где он 
    /// будет использоваться:
    ///
    ///     xmlns:MyNamespace="clr-namespace:Editor.Controls;assembly=Editor.Controls"
    ///
    /// Потребуется также добавить ссылку из проекта, в котором находится файл XAML,
    /// на данный проект и пересобрать во избежание ошибок компиляции:
    ///
    ///     Щелкните правой кнопкой мыши нужный проект в обозревателе решений и выберите
    ///     "Добавить ссылку"->"Проекты"->[Поиск и выбор проекта]
    ///
    ///
    /// Шаг 2)
    /// Теперь можно использовать элемент управления в файле XAML.
    ///
    ///     <MyNamespace:PropertyGrid/>
    ///
    /// </summary>
    public class PropertyGrid : Control
    {


        public Brush SelectionBrush
        {
            get { return (Brush)GetValue(SelectionBrushProperty); }
            set { SetValue(SelectionBrushProperty, value); }
        }

        // Using a DependencyProperty as the backing store for SelectionBrush.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty SelectionBrushProperty =
            DependencyProperty.Register("SelectionBrush", typeof(Brush), typeof(PropertyGrid), new PropertyMetadata(Brushes.LightBlue));




        public string PropertiesHeader
        {
            get { return (string)GetValue(PropertiesHeaderProperty); }
            set { SetValue(PropertiesHeaderProperty, value); }
        }

        // Using a DependencyProperty as the backing store for PropertiesHeader.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty PropertiesHeaderProperty =
            DependencyProperty.Register("PropertiesHeader", typeof(string), typeof(PropertyGrid), new PropertyMetadata("Property"));




        public string ValuesHeader
        {
            get { return (string)GetValue(ValuesHeaderProperty); }
            set { SetValue(ValuesHeaderProperty, value); }
        }

        // Using a DependencyProperty as the backing store for ValuesHeader.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty ValuesHeaderProperty =
            DependencyProperty.Register("ValuesHeader", typeof(string), typeof(PropertyGrid), new PropertyMetadata("Value"));





        public Brush HeaderForeground
        {
            get { return (Brush)GetValue(HeaderForegroundProperty); }
            set { SetValue(HeaderForegroundProperty, value); }
        }

        // Using a DependencyProperty as the backing store for HeaderForeground.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty HeaderForegroundProperty =
            DependencyProperty.Register("HeaderForeground", typeof(Brush), typeof(PropertyGrid), new PropertyMetadata(Brushes.White));



        public Brush HeaderBackground
        {
            get { return (Brush)GetValue(HeaderBackgroundProperty); }
            set { SetValue(HeaderBackgroundProperty, value); }
        }

        // Using a DependencyProperty as the backing store for HeaderBackground.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty HeaderBackgroundProperty =
            DependencyProperty.Register("HeaderBackground", typeof(Brush), typeof(PropertyGrid), new PropertyMetadata(Brushes.DarkSlateGray));


        public Brush CellBorderBrush
        {
            get { return (Brush)GetValue(CellBorderBrushProperty); }
            set { SetValue(CellBorderBrushProperty, value); }
        }

        // Using a DependencyProperty as the backing store for CellBorderBrush.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty CellBorderBrushProperty =
            DependencyProperty.Register("CellBorderBrush", typeof(Brush), typeof(PropertyGrid), new PropertyMetadata(Brushes.DarkGray));


        static PropertyGrid()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PropertyGrid), new FrameworkPropertyMetadata(typeof(PropertyGrid)));
        }
    }
}
