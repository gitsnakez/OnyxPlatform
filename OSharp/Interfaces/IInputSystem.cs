using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OSharp.Interfaces
{
    public interface IInputSystem
    {
        void SetCursorPosition(O_Location point);
        void ShowCursor();
        void HideCursor();
    }
}