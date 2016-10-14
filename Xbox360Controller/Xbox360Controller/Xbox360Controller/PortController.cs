using System;
using System.Diagnostics;
using System.IO.Ports;

namespace Xbox360Controller
{
    public class PortController
    {
        private readonly SerialPort port;

        private readonly float DeadZone = 0.1f;

        private int previousCommand;

        public PortController()
        {
            port = new SerialPort("COM8", 19200, Parity.None, 8, StopBits.One);
            port.Open();
        }

        public void GetCommand(GamepadState.ThumbstickState leftStick, GamepadState.ThumbstickState rightStick)
        {
            var turnSubcommand = GetSubcommand(leftStick.Position.X, 4, 12);
            var engineSubcommand = GetSubcommand(rightStick.Position.Y, 2, 3);

            engineSubcommand = engineSubcommand << 5;

            var fullCommand = 0;
            fullCommand |= turnSubcommand;
            fullCommand |= engineSubcommand;

            SendCommand(fullCommand);
        }

        private int GetSubcommand(float power, int directionBitIndex, int stepsCount)
        {
            var absolutePower = Math.Abs(power);
            if (absolutePower <= DeadZone)
            {
                return (0);
            }

            var directionBit = power > 0 ? 1 : 0;
            var directionMask = directionBit << directionBitIndex;

            var convertedPower = (int)(((absolutePower - DeadZone) / 0.9) * (stepsCount + 1));
            var commandData = convertedPower;
            commandData |= directionMask;

            return commandData;
        }

        private int GetEngineSubcommand(GamepadState.ThumbstickState rightStick)
        {
            var enginePower = rightStick.Position.Y;
            var absoluteEnginePower = Math.Abs(enginePower);
            if (absoluteEnginePower <= DeadZone)
            {
                return (0);
            }

            var directionBit = enginePower > 0 ? 1 : 0;
            var directionMask = directionBit << 2;
            var power = absoluteEnginePower - DeadZone;

            var convertedPower = (int)((power / 0.9) * 4);
            var commandData = convertedPower;
            commandData |= directionMask;

            return (commandData);
        }

        private int GetTurnSubcommand(GamepadState.ThumbstickState leftStick)
        {
            var turnPower = leftStick.Position.X;
            var absoluteTurnPower = Math.Abs(turnPower);
            if (absoluteTurnPower <= DeadZone)
            {
                return 0;
            }

            var directionBit = turnPower > 0 ? 1 : 0;
            var directionMask = directionBit << 4;

            var power = absoluteTurnPower - DeadZone;
            var convertedPower = (int)((power / 0.9) * 13);
            var commandData = convertedPower;
            commandData |= directionMask;

            return commandData;
        }

        private void SendCommand(int command)
        {
            if (previousCommand != command)
            {
                try
                {
                    var byteData = (byte)command;
                    port.Write(new[] { byteData }, 0, 1);
                    Trace.WriteLine(byteData);
                }
                catch { }

                previousCommand = command;
            }


        }
    }
}
