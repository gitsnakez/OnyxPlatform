using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OSharp
{
    public static class Console
    {
        public static ITransConsoleCallback Callback;

        public static string GetCommands()
        {
            return "cls/clear - clear terminal history\n" +
                "close - close terminal\n" +
                "quit - shutdown application\n" +
                "showpos 0/1 - show position and rotation of camera\n" +
                "showgraph 0/1 - show app information\n" +
                "showhud 0/1 - draw hud\n" +
                "new_terminal 0/1 - enable new terminal\n" +
                "sensetivity <float> - set sensetivity to camera controller (def. 0.1)\n" +
                "vsync 0/1 - set vertical synchronization\n" +
                "unload_map - unload current map.\n" +
                "map <string> - load map from game folder.\n" +
                "mat_wireframe 0/1 - set render mode to wireframe.";
        }

        public static void SendCommand(string command)
        {
            string[] strBuffer = command.Split(' ');

            if(strBuffer.Length == 1)
            {
                Callback.SendCommand(strBuffer[0]);
                return;
            }

            int i;
            float f;

            if (int.TryParse(strBuffer[1], out i))
            {
                Callback.SendCommand(strBuffer[0], i);
                return;
            }
            else if (float.TryParse(strBuffer[1].Replace(".", ","), out f))
            {
                Callback.SendCommand(strBuffer[0], f);
                return;
            }
            else
                Callback.SendCommand(strBuffer[0], strBuffer[1]);
        }
    }
}