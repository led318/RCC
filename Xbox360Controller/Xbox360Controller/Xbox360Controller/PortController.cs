using System.IO.Ports;

namespace Xbox360Controller
{
    public class PortController
    {
        private readonly SerialPort port;

        private readonly float dead = 0.1f;

        private GamepadState.ThumbstickState previousLeftStick;

        private GamepadState.ThumbstickState previousRightStick;
        
        public PortController()
        {
            previousLeftStick = new GamepadState.ThumbstickState();
            previousRightStick = new GamepadState.ThumbstickState();

            port = new SerialPort("COM4", 9600, Parity.None, 8, StopBits.One);
            port.Open();            
        }


        public void GetCommand(GamepadState.ThumbstickState leftStick, GamepadState.ThumbstickState rightStick)
        {
            var turnLeft = previousLeftStick.Position.X >= -dead && leftStick.Position.X < -dead;
            var turnRight = previousLeftStick.Position.X <= dead && leftStick.Position.X > dead;
            var turnStop = (previousLeftStick.Position.X > dead || previousLeftStick.Position.X < -dead)
                && (leftStick.Position.X <= dead && leftStick.Position.X >= -dead);

            if(turnLeft)
                SendCommand("l");
            else if (turnRight)
                SendCommand("r");
            else if(turnStop)
                SendCommand("m");

            var moveBack = previousRightStick.Position.Y >= -dead && rightStick.Position.Y < -dead;
            var moveForward = previousRightStick.Position.Y <= dead && rightStick.Position.Y > dead;
            var moveStop = (previousRightStick.Position.Y > dead || previousRightStick.Position.Y < -dead)
                && (rightStick.Position.Y <= dead && rightStick.Position.Y >= -dead);

            if (moveForward)
                SendCommand("f");
            else if (moveBack)
                SendCommand("b");
            else if (moveStop)
                SendCommand("s");

            previousLeftStick = leftStick;
            previousRightStick = rightStick;
        }

        private void SendCommand(string direction)
        {
            try
            {
                port.Write(direction);
            }
            catch { }
        }
    }
}
