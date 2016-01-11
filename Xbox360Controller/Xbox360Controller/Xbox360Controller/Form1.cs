using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Xbox360Controller
{
    public partial class Form1 : Form
    {
        Point leftStickOrigin, rightStickOrigin;
        Rectangle leftPieRect, rightPieRect;
        GamepadState controls;

        SolidBrush orange, red, green, blue, lightGray, darkGray;

        Random rand = new Random();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            controls = new GamepadState(0);

            leftStickOrigin = new Point(110, 80);
            rightStickOrigin = new Point(300, 160);

            leftPieRect = new Rectangle(80, 50, 60, 60);
            rightPieRect = new Rectangle(270, 130, 60, 60);

            orange = new SolidBrush(Color.FromArgb(100, 255, 165, 0));
            red = new SolidBrush(Color.FromArgb(100, 255, 0, 0));
            green = new SolidBrush(Color.FromArgb(100, 0, 255, 0));
            blue = new SolidBrush(Color.FromArgb(100, 0, 0, 255));
            lightGray = new SolidBrush(Color.FromArgb(80, 10, 10, 10));
            darkGray = new SolidBrush(Color.FromArgb(100, 20, 20, 20));

            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            controls.Update();
            pictureBox1.Refresh();
        }
        
        private float getLeftAngle()
        {
            if (controls.LeftStick.Position.Y == 0 && controls.LeftStick.Position.X == 0)
                return 0;

            double dy = leftStickOrigin.Y - controls.LeftStick.Position.Y * 1000;
            double dx = controls.LeftStick.Position.X * 1000 - leftStickOrigin.X;
            float val = (float)(Math.Atan2(dy, dx) * (double)57.295779513082320876798154814105);

            if (Math.Abs(val) == val)
                return val;
            else
                return val + 360;
        }

        private float getRightAngle()
        {
            if (controls.RightStick.Position.Y == 0 && controls.RightStick.Position.X == 0)
                return 0;

            double dy = rightStickOrigin.Y - controls.RightStick.Position.Y * 1000;
            double dx = controls.RightStick.Position.X * 1000 - rightStickOrigin.X;
            float val = (float)(Math.Atan2(dy, dx) * (double)57.295779513082320876798154814105);

            if (Math.Abs(val) == val)
                return val;
            else
                return val + 360;
        }

        private void LeftVib_ValueChanged(object sender, EventArgs e)
        {
            controls.Vibrate((float)LeftVib.Value, (float)RightVib.Value);
        }

        private void RightVib_ValueChanged(object sender, EventArgs e)
        {
            controls.Vibrate((float)LeftVib.Value, (float)RightVib.Value);
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.FillPie(orange, leftPieRect, 0, getLeftAngle());
            e.Graphics.FillPie(orange, rightPieRect, 0, getRightAngle());

            if(controls.LeftStick.Clicked)
                e.Graphics.FillEllipse(Brushes.Magenta, leftStickOrigin.X - 13, leftStickOrigin.Y - 13, 22, 22);
            if (controls.RightStick.Clicked)
                e.Graphics.FillEllipse(Brushes.Magenta, rightStickOrigin.X - 9, rightStickOrigin.Y - 13, 22, 22);

            if (controls.DPad.Up)
                e.Graphics.FillEllipse(lightGray, 160, 130, 22, 22);
            if (controls.DPad.Right)
                e.Graphics.FillEllipse(lightGray, 186, 154, 22, 22);
            if (controls.DPad.Down)
                e.Graphics.FillEllipse(lightGray, 160, 178, 22, 22);
            if (controls.DPad.Left)
                e.Graphics.FillEllipse(lightGray, 138, 154, 22, 22);
             
            if(controls.Y)
                e.Graphics.FillEllipse(orange, 348, 37, 34, 34);
            if (controls.B)
                e.Graphics.FillEllipse(red, 382, 74, 34, 34);
            if (controls.A)
                e.Graphics.FillEllipse(green, 348, 109, 34, 34);
            if (controls.X)
                e.Graphics.FillEllipse(blue, 315, 74, 34, 34);

            if(controls.Back)
                e.Graphics.FillEllipse(darkGray, 180, 80, 25, 22);
            if (controls.Start)
                e.Graphics.FillEllipse(darkGray, 272, 80, 25, 22);

            if(controls.LeftShoulder)
                e.Graphics.FillEllipse(darkGray, 6, 25, 60, 20);
            if (controls.RightShoulder)
                e.Graphics.FillEllipse(darkGray, 412, 25, 60, 20);

            leftTrig.Value = (int)(controls.LeftTrigger * 100);
            rightTrig.Value = (int)(controls.RightTrigger * 100);

            extendedInfo.Text = "Controller Connected: " + controls.Connected + "\n";

            extendedInfo.Text += "Buttons Pressed: (Y: " + controls.Y + ", B: " + controls.B +
                ", A: " + controls.A + ", X: " + controls.X + ")\n";

            extendedInfo.Text += "DPad Buttons Pressed: (Up: " + controls.DPad.Up +
                ", Right: " + controls.DPad.Right + ", Down: " + controls.DPad.Down +
                ", Left: " + controls.DPad.Left + ")\n";

            extendedInfo.Text += "Left Stick: " + controls.LeftStick.Position +
                ", Right Stick: " + controls.RightStick.Position + "\n";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            timer2.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer2.Stop();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            LeftVib.Value = (decimal)rand.NextDouble();
            RightVib.Value = (decimal)rand.NextDouble();
            timer2.Interval = rand.Next(2000, 6000);
        }

        private void cont1_CheckedChanged(object sender, EventArgs e)
        {
            controls.Vibrate(0, 0);
            controls = new GamepadState(SlimDX.XInput.UserIndex.One);
            controls.Vibrate((float)LeftVib.Value, (float)RightVib.Value);
        }

        private void cont2_CheckedChanged(object sender, EventArgs e)
        {
            controls.Vibrate(0, 0);
            controls = new GamepadState(SlimDX.XInput.UserIndex.Two);
            controls.Vibrate((float)LeftVib.Value, (float)RightVib.Value);
        }

        private void cont3_CheckedChanged(object sender, EventArgs e)
        {
            controls.Vibrate(0, 0);
            controls = new GamepadState(SlimDX.XInput.UserIndex.Three);
            controls.Vibrate((float)LeftVib.Value, (float)RightVib.Value);
        }

        private void cont4_CheckedChanged(object sender, EventArgs e)
        {
            controls.Vibrate(0, 0);
            controls = new GamepadState(SlimDX.XInput.UserIndex.Four);
            controls.Vibrate((float)LeftVib.Value, (float)RightVib.Value);
        }

        private void timeRefersh_ValueChanged(object sender, EventArgs e)
        {
            timer1.Interval = (int)timeRefersh.Value;
        }
    }
}
