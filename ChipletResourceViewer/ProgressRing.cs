using System;
using System.Collections.Generic;
using System.ComponentModel;
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

namespace ChipletResourceViewer
{
    /// <summary>
    /// Follow steps 1a or 1b and then 2 to use this custom control in a XAML file.
    ///
    /// Step 1a) Using this custom control in a XAML file that exists in the current project.
    /// Add this XmlNamespace attribute to the root element of the markup file where it is 
    /// to be used:
    ///
    ///     xmlns:MyNamespace="clr-namespace:ChipletResourceViewer"
    ///
    ///
    /// Step 1b) Using this custom control in a XAML file that exists in a different project.
    /// Add this XmlNamespace attribute to the root element of the markup file where it is 
    /// to be used:
    ///
    ///     xmlns:MyNamespace="clr-namespace:ChipletResourceViewer;assembly=ChipletResourceViewer"
    ///
    /// You will also need to add a project reference from the project where the XAML file lives
    /// to this project and Rebuild to avoid compilation errors:
    ///
    ///     Right click on the target project in the Solution Explorer and
    ///     "Add Reference"->"Projects"->[Browse to and select this project]
    ///
    ///
    /// Step 2)
    /// Go ahead and use your control in the XAML file.
    ///
    ///     <MyNamespace:ProgressRing/>
    ///
    /// </summary>
    [TemplateVisualState(Name = "Inactive", GroupName = "ActiveStates")]
    [TemplateVisualState(Name = "Active", GroupName = "ActiveStates")]
    public class ProgressRing : Control
    {
        static ProgressRing()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(ProgressRing), new FrameworkPropertyMetadata(typeof(ProgressRing)));
        }

        public ProgressRing()
        {
            this.SizeChanged += OnSizeChanged;
            UpdateEllipseDiameter();
            UpdateEllipseOffset();
        }

        #region Appearance
        [Category("Appearance")]
        public bool IsActive
        {
            get { return (bool)GetValue(IsActiveProperty); }
            set { SetValue(IsActiveProperty, value); }
        }

        public static readonly DependencyProperty IsActiveProperty = DependencyProperty.Register("IsActive", typeof(bool), typeof(ProgressRing), new PropertyMetadata(false, IsActiveChanged));

        private static void IsActiveChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var progressRing = d as ProgressRing;
            if (progressRing != null)
            {
                progressRing.UpdateActiveState();
            }
        }

        private void UpdateActiveState()
        {
            if (this.IsActive)
            {
                VisualStateManager.GoToState(this, "Active", true);
            }
            else
            {
                VisualStateManager.GoToState(this, "Inactive", true);
            }
        }
        #endregion
        #region MaxSideLength
        [Category("Layout")]
        public double MaxSideLength
        {
            get { return (double)GetValue(MaxSideLengthProperty); }
            set { SetValue(MaxSideLengthProperty, value); }
        }

        public static readonly DependencyProperty MaxSideLengthProperty = DependencyProperty.Register("MaxSideLength", typeof(double), typeof(ProgressRing), new PropertyMetadata(default(double)));

        private void OnSizeChanged(object sender, SizeChangedEventArgs e)
        {
            this.UpdateMaxSideLength();
        }

        private void UpdateMaxSideLength()
        {
            if (this.ActualWidth <= 25)
            {
                this.MaxSideLength = 20;
            }
            else
            {
                this.MaxSideLength = this.ActualWidth - 5;
            }
        }
        #endregion
        #region EllipseDiameter
        [Category("Layout")]
        public double EllipseDiameter
        {
            get { return (double)GetValue(EllipseDiameterProperty); }
            set { SetValue(EllipseDiameterProperty, value); }
        }

        public static readonly DependencyProperty EllipseDiameterProperty = DependencyProperty.Register("EllipseDiameter", typeof(double), typeof(ProgressRing), new PropertyMetadata(default(double)));

        private void UpdateEllipseDiameter()
        {
            if (this.ActualWidth <= 25)
            {
                this.EllipseDiameter = 3;
            }
            else
            {
                this.EllipseDiameter = (this.ActualWidth / 10) + 0.5;
            }
        }
        #endregion
        #region EllipseOffset
        [Category("Layout")]
        public Thickness EllipseOffset
        {
            get { return (Thickness)GetValue(EllipseOffsetProperty); }
            set { SetValue(EllipseOffsetProperty, value); }
        }

        public static readonly DependencyProperty EllipseOffsetProperty = DependencyProperty.Register("EllipseOffset", typeof(Thickness), typeof(ProgressRing), new PropertyMetadata(default(Thickness)));

        private void UpdateEllipseOffset()
        {
            if (this.ActualWidth <= 25)
            {
                this.EllipseOffset = new Thickness(0, 7, 0, 0);
                return;
            }
            else if (this.ActualWidth <= 30)
            {
                var top = this.ActualWidth * (9 / 20) - (9 / 2);
                this.EllipseOffset = new Thickness(0, top, 0, 0);
                return;
            }
            else
            {
                var top = this.ActualWidth * (2 / 5) - 2;
                this.EllipseOffset = new Thickness(0, top, 0, 0);
            }
        }
        #endregion
    }
}
