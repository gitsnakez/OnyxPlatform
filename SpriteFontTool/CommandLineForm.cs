using OSharp;
using System.Windows.Forms;
using System.Windows.Media;

namespace SpriteFontTool
{
    public partial class CommandLineForm : Form
    {
        public CommandLineForm(string commandLine)
        {
            InitializeComponent();
            OWM.DwmSetWindowAttribute(Handle, DWM.ImmersiveMode.Dark);
            OWM.DwmSetWindowAttribute(Handle, DWM.Color.Title, Color.FromArgb(255, 32, 32, 32));
            CommandLineTextBox.Text = commandLine;
        }
    }
}
