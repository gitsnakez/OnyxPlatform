using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace OSharp
{
    public partial class TerminalMillenium : Form, ITerminal
    {
        public TerminalMillenium()
        {
            InitializeComponent();
            OWM.SetClassicWindowCaption(Handle, true);
        }

        public static List<string> commands_history = new List<string>();
        public BindingSource bs = new BindingSource();
        public bool isPressingExit = false;
        public string buildTime = null;

        private void TerminalMillenium_Load(object sender, EventArgs e)
        {
            outPutTextBox.Text += $"  :: - - - - - - - - - - - ::\r\n  | Onyx Platform©          |\r\n  | {buildTime}  |\r\n  :: - - - - - - - - - - - ::\r\n\r\nsend \"help\" command to get basic command list.\n\n";
            bs.DataSource = commands_history;
            commandPrompt.DataSource = bs;
        }

        private void commandsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShowHelpCommands();
        }

        private void ShowHelpCommands()
        {
            Insert(":: COMMANDS ::", Color.Black);
            Insert(Console.GetCommands(), Color.DimGray);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void Insert(string output, Color color)
        {
            Color mainColor = outPutTextBox.ForeColor;
            
            outPutTextBox.SelectionStart = outPutTextBox.Text.Length - 1;
            outPutTextBox.SelectionColor = color;
            outPutTextBox.SelectedText = $"{output}\n";
            outPutTextBox.SelectionColor = mainColor;
            outPutTextBox.SelectionStart = outPutTextBox.Text.Length - 1;
        }

        public static TerminalMillenium terminal = new TerminalMillenium();

        private void TerminalMillenium_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            // Check for void / space, tab, etc.
            if (commandPrompt.Text.Trim() == "")
                return;
            else
                Insert($">{commandPrompt.Text}\n", Color.Black);

            if (commandPrompt.Items.Count == 0 || commandPrompt.Items[0].ToString() != commandPrompt.Text.Trim())
            {
                commands_history.Insert(0, commandPrompt.Text.Trim());
                bs = new BindingSource();
                bs.DataSource = commands_history;
                commandPrompt.DataSource = bs;
            }

            // Check for clear
            switch (commandPrompt.Text.Trim())
            {
                case "help": ShowHelpCommands(); break;
                case "cls": outPutTextBox.Clear(); break;
                case "clear": outPutTextBox.Clear(); break;
                case "close": Close(); break;
                default: Console.SendCommand(commandPrompt.Text.Trim()); break;
            }

            // Clear cmd prompt
            commandPrompt.Text = "";
        }

        private void TerminalMillenium_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch(e.KeyChar)
            {
                case '`': isPressingExit = true; break;
                case (char)Keys.Enter: sendButton.PerformClick(); break;
            }
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            outPutTextBox.Clear();
        }

        private void TerminalMillenium_KeyUp(object sender, KeyEventArgs e)
        {
            if (isPressingExit) { Close(); isPressingExit = false; }
        }

        bool indexChanging = false;

        private void commandPrompt_SelectedIndexChanged(object sender, EventArgs e)
        {
            indexChanging = true;
        }

        private void commandPrompt_TextUpdate(object sender, EventArgs e)
        {/*
            if(!indexChanging)
            {
                List<string> list = new List<string>();
                foreach (string command in Console.commands_declorations)
                {
                    if(command.StartsWith(commandPrompt.Text.Trim()))
                    {
                        list.Add(command);
                    }
                }
                list.Sort();

                bs = new BindingSource();
                bs.DataSource = list;
                commandPrompt.DataSource = bs;

                commandPrompt.DroppedDown = true;
            }*/
            if(commandPrompt.Items.Count > 0)
            {
                commandPrompt.DroppedDown = true;
                commandPrompt.Select(commandPrompt.Text.Length, 0);
            }
        }

        private void clearCommandHistoryToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commands_history = new List<string>();
            bs = new BindingSource();
            bs.DataSource = commands_history;
            commandPrompt.DataSource = bs;
        }

        public bool CheckVisible => Visible;

        public bool CheckFocus => Focused;

        public void SetVisibility(bool visible)
        {
            if(visible)
                Show();
            else
                Hide();
        }

        private void tryNewTerminalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Console.SendCommand("new_terminal 1");
        }
    }
}
