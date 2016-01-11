namespace Xbox360Controller
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.LeftVib = new System.Windows.Forms.NumericUpDown();
            this.RightVib = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.cont1 = new System.Windows.Forms.RadioButton();
            this.cont2 = new System.Windows.Forms.RadioButton();
            this.cont3 = new System.Windows.Forms.RadioButton();
            this.cont4 = new System.Windows.Forms.RadioButton();
            this.leftTrig = new System.Windows.Forms.ProgressBar();
            this.rightTrig = new System.Windows.Forms.ProgressBar();
            this.extendedInfo = new System.Windows.Forms.RichTextBox();
            this.timeRefersh = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.LeftVib)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RightVib)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeRefersh)).BeginInit();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 1;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // LeftVib
            // 
            this.LeftVib.DecimalPlaces = 2;
            this.LeftVib.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.LeftVib.Location = new System.Drawing.Point(209, 282);
            this.LeftVib.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.LeftVib.Name = "LeftVib";
            this.LeftVib.Size = new System.Drawing.Size(48, 20);
            this.LeftVib.TabIndex = 1;
            this.LeftVib.ValueChanged += new System.EventHandler(this.LeftVib_ValueChanged);
            // 
            // RightVib
            // 
            this.RightVib.DecimalPlaces = 2;
            this.RightVib.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.RightVib.Location = new System.Drawing.Point(273, 282);
            this.RightVib.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.RightVib.Name = "RightVib";
            this.RightVib.Size = new System.Drawing.Size(48, 20);
            this.RightVib.TabIndex = 1;
            this.RightVib.ValueChanged += new System.EventHandler(this.RightVib_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(152, 284);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Vibration:";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Xbox360Controller.Properties.Resources.xbox360controller;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(474, 374);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(155, 308);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(80, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "Start Random";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(241, 308);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(80, 23);
            this.button2.TabIndex = 4;
            this.button2.Text = "Stop Random";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // timer2
            // 
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // cont1
            // 
            this.cont1.AutoSize = true;
            this.cont1.BackColor = System.Drawing.Color.Transparent;
            this.cont1.Checked = true;
            this.cont1.Location = new System.Drawing.Point(191, 57);
            this.cont1.Name = "cont1";
            this.cont1.Size = new System.Drawing.Size(31, 17);
            this.cont1.TabIndex = 5;
            this.cont1.TabStop = true;
            this.cont1.Text = "1";
            this.cont1.UseVisualStyleBackColor = false;
            this.cont1.CheckedChanged += new System.EventHandler(this.cont1_CheckedChanged);
            // 
            // cont2
            // 
            this.cont2.AutoSize = true;
            this.cont2.BackColor = System.Drawing.Color.Transparent;
            this.cont2.Location = new System.Drawing.Point(262, 57);
            this.cont2.Name = "cont2";
            this.cont2.Size = new System.Drawing.Size(31, 17);
            this.cont2.TabIndex = 5;
            this.cont2.TabStop = true;
            this.cont2.Text = "2";
            this.cont2.UseVisualStyleBackColor = false;
            this.cont2.CheckedChanged += new System.EventHandler(this.cont2_CheckedChanged);
            // 
            // cont3
            // 
            this.cont3.AutoSize = true;
            this.cont3.BackColor = System.Drawing.Color.Transparent;
            this.cont3.Location = new System.Drawing.Point(191, 114);
            this.cont3.Name = "cont3";
            this.cont3.Size = new System.Drawing.Size(31, 17);
            this.cont3.TabIndex = 5;
            this.cont3.TabStop = true;
            this.cont3.Text = "3";
            this.cont3.UseVisualStyleBackColor = false;
            this.cont3.CheckedChanged += new System.EventHandler(this.cont3_CheckedChanged);
            // 
            // cont4
            // 
            this.cont4.AutoSize = true;
            this.cont4.BackColor = System.Drawing.Color.Transparent;
            this.cont4.Location = new System.Drawing.Point(262, 114);
            this.cont4.Name = "cont4";
            this.cont4.Size = new System.Drawing.Size(31, 17);
            this.cont4.TabIndex = 5;
            this.cont4.TabStop = true;
            this.cont4.Text = "4";
            this.cont4.UseVisualStyleBackColor = false;
            this.cont4.CheckedChanged += new System.EventHandler(this.cont4_CheckedChanged);
            // 
            // leftTrig
            // 
            this.leftTrig.Location = new System.Drawing.Point(5, 7);
            this.leftTrig.Name = "leftTrig";
            this.leftTrig.Size = new System.Drawing.Size(75, 15);
            this.leftTrig.TabIndex = 7;
            // 
            // rightTrig
            // 
            this.rightTrig.Location = new System.Drawing.Point(394, 7);
            this.rightTrig.Name = "rightTrig";
            this.rightTrig.Size = new System.Drawing.Size(75, 15);
            this.rightTrig.TabIndex = 7;
            // 
            // extendedInfo
            // 
            this.extendedInfo.Location = new System.Drawing.Point(12, 380);
            this.extendedInfo.Name = "extendedInfo";
            this.extendedInfo.ReadOnly = true;
            this.extendedInfo.Size = new System.Drawing.Size(450, 83);
            this.extendedInfo.TabIndex = 8;
            this.extendedInfo.Text = "";
            // 
            // timeRefersh
            // 
            this.timeRefersh.Location = new System.Drawing.Point(241, 7);
            this.timeRefersh.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.timeRefersh.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.timeRefersh.Name = "timeRefersh";
            this.timeRefersh.Size = new System.Drawing.Size(44, 20);
            this.timeRefersh.TabIndex = 9;
            this.timeRefersh.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.timeRefersh.ValueChanged += new System.EventHandler(this.timeRefersh_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(188, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Refresh:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(474, 475);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.timeRefersh);
            this.Controls.Add(this.extendedInfo);
            this.Controls.Add(this.rightTrig);
            this.Controls.Add(this.leftTrig);
            this.Controls.Add(this.cont4);
            this.Controls.Add(this.cont3);
            this.Controls.Add(this.cont2);
            this.Controls.Add(this.cont1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.RightVib);
            this.Controls.Add(this.LeftVib);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.Text = "XBOX 360 Controls";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.LeftVib)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RightVib)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeRefersh)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.NumericUpDown LeftVib;
        private System.Windows.Forms.NumericUpDown RightVib;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.RadioButton cont1;
        private System.Windows.Forms.RadioButton cont2;
        private System.Windows.Forms.RadioButton cont3;
        private System.Windows.Forms.RadioButton cont4;
        private System.Windows.Forms.ProgressBar leftTrig;
        private System.Windows.Forms.ProgressBar rightTrig;
        private System.Windows.Forms.RichTextBox extendedInfo;
        private System.Windows.Forms.NumericUpDown timeRefersh;
        private System.Windows.Forms.Label label2;
    }
}

