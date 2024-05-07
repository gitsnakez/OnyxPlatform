namespace SpriteFontTool
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.TableLayoutPanelForFont = new System.Windows.Forms.TableLayoutPanel();
            this.labelLanguages = new System.Windows.Forms.Label();
            this.LanguagesCheckedListBox = new System.Windows.Forms.CheckedListBox();
            this.labelFastPack = new System.Windows.Forms.Label();
            this.labelSharp = new System.Windows.Forms.Label();
            this.FastPackCheckBox = new System.Windows.Forms.CheckBox();
            this.SharpCheckBox = new System.Windows.Forms.CheckBox();
            this.labelFontSize = new System.Windows.Forms.Label();
            this.FontSizeNumeric = new System.Windows.Forms.NumericUpDown();
            this.FontsComboBox = new System.Windows.Forms.ComboBox();
            this.labelFont = new System.Windows.Forms.Label();
            this.labelOutput = new System.Windows.Forms.Label();
            this.inputTableLayout = new System.Windows.Forms.TableLayoutPanel();
            this.OutputTextBox = new System.Windows.Forms.TextBox();
            this.browseOutputButton = new System.Windows.Forms.Button();
            this.BottomPanel = new System.Windows.Forms.Panel();
            this.AsGeneralCheckBox = new System.Windows.Forms.CheckBox();
            this.linkToCmdLine = new System.Windows.Forms.LinkLabel();
            this.StartPackButton = new System.Windows.Forms.Button();
            this.labelLineSpacing = new System.Windows.Forms.Label();
            this.LineSpacingNumeric = new System.Windows.Forms.NumericUpDown();
            this.labelFontStyle = new System.Windows.Forms.Label();
            this.FontStyleComboBox = new System.Windows.Forms.ComboBox();
            this.TableLayoutPanelForFont.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.FontSizeNumeric)).BeginInit();
            this.inputTableLayout.SuspendLayout();
            this.BottomPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LineSpacingNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // TableLayoutPanelForFont
            // 
            this.TableLayoutPanelForFont.AutoSize = true;
            this.TableLayoutPanelForFont.ColumnCount = 2;
            this.TableLayoutPanelForFont.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 140F));
            this.TableLayoutPanelForFont.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.TableLayoutPanelForFont.Controls.Add(this.labelFontSize, 0, 2);
            this.TableLayoutPanelForFont.Controls.Add(this.FontSizeNumeric, 1, 2);
            this.TableLayoutPanelForFont.Controls.Add(this.FontsComboBox, 1, 1);
            this.TableLayoutPanelForFont.Controls.Add(this.labelFont, 0, 1);
            this.TableLayoutPanelForFont.Controls.Add(this.labelOutput, 0, 0);
            this.TableLayoutPanelForFont.Controls.Add(this.inputTableLayout, 1, 0);
            this.TableLayoutPanelForFont.Controls.Add(this.labelLanguages, 0, 7);
            this.TableLayoutPanelForFont.Controls.Add(this.LanguagesCheckedListBox, 1, 7);
            this.TableLayoutPanelForFont.Controls.Add(this.labelFastPack, 0, 6);
            this.TableLayoutPanelForFont.Controls.Add(this.labelSharp, 0, 5);
            this.TableLayoutPanelForFont.Controls.Add(this.FastPackCheckBox, 1, 6);
            this.TableLayoutPanelForFont.Controls.Add(this.SharpCheckBox, 1, 5);
            this.TableLayoutPanelForFont.Controls.Add(this.labelLineSpacing, 0, 4);
            this.TableLayoutPanelForFont.Controls.Add(this.LineSpacingNumeric, 1, 4);
            this.TableLayoutPanelForFont.Controls.Add(this.labelFontStyle, 0, 3);
            this.TableLayoutPanelForFont.Controls.Add(this.FontStyleComboBox, 1, 3);
            this.TableLayoutPanelForFont.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TableLayoutPanelForFont.Location = new System.Drawing.Point(0, 0);
            this.TableLayoutPanelForFont.Name = "TableLayoutPanelForFont";
            this.TableLayoutPanelForFont.RowCount = 8;
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.TableLayoutPanelForFont.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.TableLayoutPanelForFont.Size = new System.Drawing.Size(600, 410);
            this.TableLayoutPanelForFont.TabIndex = 6;
            // 
            // labelLanguages
            // 
            this.labelLanguages.AutoSize = true;
            this.labelLanguages.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelLanguages.Location = new System.Drawing.Point(3, 243);
            this.labelLanguages.Margin = new System.Windows.Forms.Padding(3, 5, 3, 0);
            this.labelLanguages.Name = "labelLanguages";
            this.labelLanguages.Size = new System.Drawing.Size(89, 20);
            this.labelLanguages.TabIndex = 8;
            this.labelLanguages.Text = "Languages";
            // 
            // LanguagesCheckedListBox
            // 
            this.LanguagesCheckedListBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.LanguagesCheckedListBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(32)))), ((int)(((byte)(32)))));
            this.LanguagesCheckedListBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.LanguagesCheckedListBox.CheckOnClick = true;
            this.LanguagesCheckedListBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LanguagesCheckedListBox.ForeColor = System.Drawing.Color.White;
            this.LanguagesCheckedListBox.FormattingEnabled = true;
            this.LanguagesCheckedListBox.IntegralHeight = false;
            this.LanguagesCheckedListBox.Items.AddRange(new object[] {
            "Cyrillic",
            "Armenian",
            "Hebrew",
            "Arabic",
            "Syriac",
            "Thaana",
            "NKo",
            "Samaritan",
            "Mandaic"});
            this.LanguagesCheckedListBox.Location = new System.Drawing.Point(143, 241);
            this.LanguagesCheckedListBox.Name = "LanguagesCheckedListBox";
            this.LanguagesCheckedListBox.Size = new System.Drawing.Size(454, 166);
            this.LanguagesCheckedListBox.TabIndex = 9;
            // 
            // labelFastPack
            // 
            this.labelFastPack.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelFastPack.AutoSize = true;
            this.labelFastPack.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelFastPack.Location = new System.Drawing.Point(3, 211);
            this.labelFastPack.Name = "labelFastPack";
            this.labelFastPack.Size = new System.Drawing.Size(80, 20);
            this.labelFastPack.TabIndex = 6;
            this.labelFastPack.Text = "Fast Pack";
            // 
            // labelSharp
            // 
            this.labelSharp.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelSharp.AutoSize = true;
            this.labelSharp.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelSharp.Location = new System.Drawing.Point(3, 177);
            this.labelSharp.Name = "labelSharp";
            this.labelSharp.Size = new System.Drawing.Size(52, 20);
            this.labelSharp.TabIndex = 4;
            this.labelSharp.Text = "Sharp";
            // 
            // FastPackCheckBox
            // 
            this.FastPackCheckBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.FastPackCheckBox.AutoSize = true;
            this.FastPackCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FastPackCheckBox.Location = new System.Drawing.Point(143, 214);
            this.FastPackCheckBox.Name = "FastPackCheckBox";
            this.FastPackCheckBox.Size = new System.Drawing.Size(15, 14);
            this.FastPackCheckBox.TabIndex = 7;
            this.FastPackCheckBox.UseVisualStyleBackColor = true;
            // 
            // SharpCheckBox
            // 
            this.SharpCheckBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.SharpCheckBox.AutoSize = true;
            this.SharpCheckBox.Checked = true;
            this.SharpCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.SharpCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SharpCheckBox.Location = new System.Drawing.Point(143, 180);
            this.SharpCheckBox.Name = "SharpCheckBox";
            this.SharpCheckBox.Size = new System.Drawing.Size(15, 14);
            this.SharpCheckBox.TabIndex = 5;
            this.SharpCheckBox.UseVisualStyleBackColor = true;
            // 
            // labelFontSize
            // 
            this.labelFontSize.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelFontSize.AutoSize = true;
            this.labelFontSize.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelFontSize.Location = new System.Drawing.Point(3, 75);
            this.labelFontSize.Name = "labelFontSize";
            this.labelFontSize.Size = new System.Drawing.Size(40, 20);
            this.labelFontSize.TabIndex = 2;
            this.labelFontSize.Text = "Size";
            // 
            // FontSizeNumeric
            // 
            this.FontSizeNumeric.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.FontSizeNumeric.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FontSizeNumeric.DecimalPlaces = 1;
            this.FontSizeNumeric.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FontSizeNumeric.Increment = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.FontSizeNumeric.Location = new System.Drawing.Point(143, 72);
            this.FontSizeNumeric.Maximum = new decimal(new int[] {
            130,
            0,
            0,
            0});
            this.FontSizeNumeric.Minimum = new decimal(new int[] {
            6,
            0,
            0,
            0});
            this.FontSizeNumeric.Name = "FontSizeNumeric";
            this.FontSizeNumeric.Size = new System.Drawing.Size(454, 26);
            this.FontSizeNumeric.TabIndex = 3;
            this.FontSizeNumeric.Value = new decimal(new int[] {
            12,
            0,
            0,
            0});
            // 
            // FontsComboBox
            // 
            this.FontsComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.FontsComboBox.DisplayMember = "0";
            this.FontsComboBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FontsComboBox.FormattingEnabled = true;
            this.FontsComboBox.Location = new System.Drawing.Point(143, 37);
            this.FontsComboBox.Name = "FontsComboBox";
            this.FontsComboBox.Size = new System.Drawing.Size(454, 28);
            this.FontsComboBox.TabIndex = 0;
            // 
            // labelFont
            // 
            this.labelFont.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelFont.AutoSize = true;
            this.labelFont.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelFont.Location = new System.Drawing.Point(3, 41);
            this.labelFont.Name = "labelFont";
            this.labelFont.Size = new System.Drawing.Size(42, 20);
            this.labelFont.TabIndex = 1;
            this.labelFont.Text = "Font";
            // 
            // labelOutput
            // 
            this.labelOutput.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelOutput.AutoSize = true;
            this.labelOutput.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelOutput.Location = new System.Drawing.Point(3, 7);
            this.labelOutput.Name = "labelOutput";
            this.labelOutput.Size = new System.Drawing.Size(58, 20);
            this.labelOutput.TabIndex = 1;
            this.labelOutput.Text = "Output";
            // 
            // inputTableLayout
            // 
            this.inputTableLayout.ColumnCount = 2;
            this.inputTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.inputTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.inputTableLayout.Controls.Add(this.OutputTextBox, 0, 0);
            this.inputTableLayout.Controls.Add(this.browseOutputButton, 1, 0);
            this.inputTableLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.inputTableLayout.Location = new System.Drawing.Point(140, 0);
            this.inputTableLayout.Margin = new System.Windows.Forms.Padding(0);
            this.inputTableLayout.Name = "inputTableLayout";
            this.inputTableLayout.RowCount = 1;
            this.inputTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.inputTableLayout.Size = new System.Drawing.Size(460, 34);
            this.inputTableLayout.TabIndex = 10;
            // 
            // OutputTextBox
            // 
            this.OutputTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.OutputTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OutputTextBox.Location = new System.Drawing.Point(3, 4);
            this.OutputTextBox.Name = "OutputTextBox";
            this.OutputTextBox.Size = new System.Drawing.Size(414, 26);
            this.OutputTextBox.TabIndex = 0;
            // 
            // browseOutputButton
            // 
            this.browseOutputButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.browseOutputButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.browseOutputButton.ForeColor = System.Drawing.Color.Black;
            this.browseOutputButton.Location = new System.Drawing.Point(423, 4);
            this.browseOutputButton.Name = "browseOutputButton";
            this.browseOutputButton.Size = new System.Drawing.Size(34, 26);
            this.browseOutputButton.TabIndex = 1;
            this.browseOutputButton.Text = "...";
            this.browseOutputButton.UseVisualStyleBackColor = true;
            this.browseOutputButton.Click += new System.EventHandler(this.browseOutputButton_Click);
            // 
            // BottomPanel
            // 
            this.BottomPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(40)))), ((int)(((byte)(40)))), ((int)(((byte)(40)))));
            this.BottomPanel.Controls.Add(this.AsGeneralCheckBox);
            this.BottomPanel.Controls.Add(this.linkToCmdLine);
            this.BottomPanel.Controls.Add(this.StartPackButton);
            this.BottomPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.BottomPanel.Location = new System.Drawing.Point(0, 410);
            this.BottomPanel.Name = "BottomPanel";
            this.BottomPanel.Size = new System.Drawing.Size(600, 40);
            this.BottomPanel.TabIndex = 7;
            // 
            // AsGeneralCheckBox
            // 
            this.AsGeneralCheckBox.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.AsGeneralCheckBox.AutoSize = true;
            this.AsGeneralCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.AsGeneralCheckBox.Location = new System.Drawing.Point(357, 8);
            this.AsGeneralCheckBox.Name = "AsGeneralCheckBox";
            this.AsGeneralCheckBox.Size = new System.Drawing.Size(131, 24);
            this.AsGeneralCheckBox.TabIndex = 2;
            this.AsGeneralCheckBox.Text = "Set as general";
            this.AsGeneralCheckBox.UseVisualStyleBackColor = true;
            // 
            // linkToCmdLine
            // 
            this.linkToCmdLine.ActiveLinkColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.linkToCmdLine.AutoSize = true;
            this.linkToCmdLine.LinkColor = System.Drawing.Color.Gray;
            this.linkToCmdLine.Location = new System.Drawing.Point(3, 22);
            this.linkToCmdLine.Name = "linkToCmdLine";
            this.linkToCmdLine.Size = new System.Drawing.Size(100, 13);
            this.linkToCmdLine.TabIndex = 1;
            this.linkToCmdLine.TabStop = true;
            this.linkToCmdLine.Text = "show command line";
            this.linkToCmdLine.VisitedLinkColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.linkToCmdLine.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkToCmdLine_LinkClicked);
            // 
            // StartPackButton
            // 
            this.StartPackButton.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.StartPackButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StartPackButton.ForeColor = System.Drawing.Color.Black;
            this.StartPackButton.Location = new System.Drawing.Point(494, 5);
            this.StartPackButton.Name = "StartPackButton";
            this.StartPackButton.Size = new System.Drawing.Size(100, 30);
            this.StartPackButton.TabIndex = 0;
            this.StartPackButton.Text = "Pack";
            this.StartPackButton.UseVisualStyleBackColor = true;
            this.StartPackButton.Click += new System.EventHandler(this.StartPackButton_Click);
            // 
            // labelLineSpacing
            // 
            this.labelLineSpacing.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelLineSpacing.AutoSize = true;
            this.labelLineSpacing.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelLineSpacing.Location = new System.Drawing.Point(3, 143);
            this.labelLineSpacing.Name = "labelLineSpacing";
            this.labelLineSpacing.Size = new System.Drawing.Size(98, 20);
            this.labelLineSpacing.TabIndex = 6;
            this.labelLineSpacing.Text = "Line spacing";
            // 
            // LineSpacingNumeric
            // 
            this.LineSpacingNumeric.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.LineSpacingNumeric.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.LineSpacingNumeric.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LineSpacingNumeric.Location = new System.Drawing.Point(143, 140);
            this.LineSpacingNumeric.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.LineSpacingNumeric.Name = "LineSpacingNumeric";
            this.LineSpacingNumeric.Size = new System.Drawing.Size(454, 26);
            this.LineSpacingNumeric.TabIndex = 3;
            // 
            // labelFontStyle
            // 
            this.labelFontStyle.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.labelFontStyle.AutoSize = true;
            this.labelFontStyle.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelFontStyle.Location = new System.Drawing.Point(3, 109);
            this.labelFontStyle.Name = "labelFontStyle";
            this.labelFontStyle.Size = new System.Drawing.Size(78, 20);
            this.labelFontStyle.TabIndex = 6;
            this.labelFontStyle.Text = "Font style";
            // 
            // FontStyleComboBox
            // 
            this.FontStyleComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.FontStyleComboBox.DisplayMember = "0";
            this.FontStyleComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FontStyleComboBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FontStyleComboBox.FormattingEnabled = true;
            this.FontStyleComboBox.Items.AddRange(new object[] {
            "Regular",
            "Bold",
            "Italic",
            "Strikeout",
            "Underline"});
            this.FontStyleComboBox.Location = new System.Drawing.Point(143, 105);
            this.FontStyleComboBox.Name = "FontStyleComboBox";
            this.FontStyleComboBox.Size = new System.Drawing.Size(454, 28);
            this.FontStyleComboBox.TabIndex = 0;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(32)))), ((int)(((byte)(32)))));
            this.ClientSize = new System.Drawing.Size(600, 450);
            this.Controls.Add(this.TableLayoutPanelForFont);
            this.Controls.Add(this.BottomPanel);
            this.ForeColor = System.Drawing.Color.White;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(366, 289);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Sprite Font Tool";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.TableLayoutPanelForFont.ResumeLayout(false);
            this.TableLayoutPanelForFont.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.FontSizeNumeric)).EndInit();
            this.inputTableLayout.ResumeLayout(false);
            this.inputTableLayout.PerformLayout();
            this.BottomPanel.ResumeLayout(false);
            this.BottomPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LineSpacingNumeric)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel TableLayoutPanelForFont;
        private System.Windows.Forms.Label labelLanguages;
        private System.Windows.Forms.CheckedListBox LanguagesCheckedListBox;
        private System.Windows.Forms.Label labelFastPack;
        private System.Windows.Forms.Label labelSharp;
        private System.Windows.Forms.CheckBox FastPackCheckBox;
        private System.Windows.Forms.CheckBox SharpCheckBox;
        private System.Windows.Forms.Label labelFontSize;
        private System.Windows.Forms.NumericUpDown FontSizeNumeric;
        private System.Windows.Forms.ComboBox FontsComboBox;
        private System.Windows.Forms.Label labelFont;
        private System.Windows.Forms.Label labelOutput;
        private System.Windows.Forms.TableLayoutPanel inputTableLayout;
        private System.Windows.Forms.TextBox OutputTextBox;
        private System.Windows.Forms.Button browseOutputButton;
        private System.Windows.Forms.Panel BottomPanel;
        private System.Windows.Forms.Button StartPackButton;
        private System.Windows.Forms.LinkLabel linkToCmdLine;
        private System.Windows.Forms.CheckBox AsGeneralCheckBox;
        private System.Windows.Forms.Label labelLineSpacing;
        private System.Windows.Forms.NumericUpDown LineSpacingNumeric;
        private System.Windows.Forms.Label labelFontStyle;
        private System.Windows.Forms.ComboBox FontStyleComboBox;
    }
}