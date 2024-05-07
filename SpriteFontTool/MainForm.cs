using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.Drawing.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using OSharp;
using System.Diagnostics;
using System.Windows.Media;
using System.Windows;
using System.IO;

namespace SpriteFontTool
{
    public partial class MainForm : Form
    {
        private string AppPath = "";
        private string FontPath = "";
        private string CommandLine = "";
            
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            OWM.DwmSetWindowAttribute(Handle, DWM.ImmersiveMode.Dark);
            OWM.DwmSetWindowAttribute(Handle, DWM.Color.Title, Color.FromArgb(255, 32, 32, 32));

            InstalledFontCollection fontCol = new InstalledFontCollection();
            for (int x = 0; x <= fontCol.Families.Length - 1; x++)
            {
                FontsComboBox.Items.Add(fontCol.Families[x].Name);
            }
            FontsComboBox.SelectedIndex = 0;
            FontStyleComboBox.SelectedIndex = 0;

            OutputTextBox.Text = AppDomain.CurrentDomain.BaseDirectory;
            OutputTextBox.Text = Regex.Replace(AppDomain.CurrentDomain.BaseDirectory, @"\\bin\\$", "\\resources\\fonts\\");
        }

        private void browseOutputButton_Click(object sender, EventArgs e)
        {
            CommonOpenFileDialog dialog = new CommonOpenFileDialog();
            dialog.InitialDirectory = OutputTextBox.Text;
            dialog.IsFolderPicker = true;
            if (dialog.ShowDialog() == CommonFileDialogResult.Ok)
                OutputTextBox.Text = dialog.FileName;
        }

        void MakeInput()
        {
            AppPath = AppDomain.CurrentDomain.BaseDirectory + "MakeSpriteFont.exe";
            var spriteFont = new SpriteFont();

            FontPath = OutputTextBox.Text.Trim() + Regex.Replace(FontsComboBox.Text.Trim(), @"\s", "") + ".spritefont";

            spriteFont.output_path = FontPath;
            spriteFont.fontname = FontsComboBox.Text.Trim();
            spriteFont.style = FontStyleComboBox.Text.Trim();
            spriteFont.linespacing = (int)LineSpacingNumeric.Value;
            spriteFont.sharp = SharpCheckBox.Checked;
            spriteFont.fastpack = FastPackCheckBox.Checked;
            spriteFont.fontsize = (float)FontSizeNumeric.Value;

            string[] array = new String[LanguagesCheckedListBox.CheckedItems.Count];
            LanguagesCheckedListBox.CheckedItems.CopyTo(array, 0);

            spriteFont.ConvertLanguagesToRegions(array);
            CommandLine = SpriteFont.MakeFont(spriteFont);
        }

        private void linkToCmdLine_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            MakeInput();
            new CommandLineForm(CommandLine).ShowDialog(this);
        }

        private void StartPackButton_Click(object sender, EventArgs e)
        {
            MakeInput();

            Process makespritefont = Process.Start(new ProcessStartInfo
            {
                FileName = AppPath,
                Arguments = CommandLine,
                WindowStyle = ProcessWindowStyle.Normal
            });

            if(AsGeneralCheckBox.Checked)
            {
                makespritefont.WaitForExit();
                if (File.Exists($"{OutputTextBox.Text}General.spritefont"))
                    File.Delete($"{OutputTextBox.Text}General.spritefont");

                File.Move(FontPath, $"{OutputTextBox.Text}General.spritefont");
            }
        }
    }
}
