using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Automation.Peers;
using System.Windows.Automation.Provider;
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
    /// Логика взаимодействия для TerminalWindow.xaml
    /// </summary>
    public partial class TerminalWindow : Window, ITerminal
    {
        public TerminalWindow()
        {
            InitializeComponent();
        }

        public static TerminalWindow terminal = new TerminalWindow();

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            OWM.DwmSetWindowAttribute(this, DWM.Color.Title, Color.FromRgb(48, 48, 48));
            OWM.DwmSetWindowAttribute(this, DWM.ImmersiveMode.Dark);
            commandPrompt.Focus();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        public bool CheckVisible {
            get
            {
                if (Visibility == Visibility.Visible)
                    return true;
                else
                    return false;
            }
        }

        private void ShowHelpCommands()
        {
            Insert(">> COMMANDS <<", Colors.White);
            Insert(Console.GetCommands(), Colors.DarkGray);
        }

        public bool CheckFocus => IsFocused;

        public void SetVisibility(bool visible)
        {
            if (visible)
                Show();
            else
                Hide();
        }

        bool isPressingExit = false;

        private void Insert(string output, Color color)
        {
            TextRange tr = new TextRange(outPutTextBox.Document.ContentEnd, outPutTextBox.Document.ContentEnd);
            tr.Text = output + Environment.NewLine;
            tr.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(color));
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Oem3: isPressingExit = true; break;
                case Key.Enter:
                    ButtonAutomationPeer peer = new ButtonAutomationPeer(sendButton);
                    IInvokeProvider invokeProv = peer.GetPattern(PatternInterface.Invoke) as IInvokeProvider;
                    invokeProv.Invoke();
                break;
            }
        }

        private void Window_KeyUp(object sender, System.Windows.Input.KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Oem3: if(isPressingExit)Close(); isPressingExit = false; break;
            }
        }

        private void OldTerminalMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Console.SendCommand("new_terminal 0");
        }

        private void PopupMsgMenuItem_Click(object sender, RoutedEventArgs e)
        {
            PopupMessage.Show("We are solving problem...\nPlease wait!");
        }

        private void sendButton_Click(object sender, RoutedEventArgs e)
        {
            // Check for void / space, tab, etc.
            if (commandPrompt.Text.Trim() == "")
                return;
            else
                Insert($">{commandPrompt.Text}\n", Colors.White);

            // Check for clear
            switch (commandPrompt.Text.Trim())
            {
                case "help": ShowHelpCommands(); break;
                case "cls": outPutTextBox.Document.Blocks.Clear(); break;
                case "clear": outPutTextBox.Document.Blocks.Clear(); break;
                case "close": Close(); break;
                default: Console.SendCommand(commandPrompt.Text.Trim()); break;
            }

            // Clear cmd prompt
            commandPrompt.Text = "";
        }

        private void CommandsMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ShowHelpCommands();
        }

        private void CloseMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void ExitAppMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Console.SendCommand("quit");
        }
    }
}