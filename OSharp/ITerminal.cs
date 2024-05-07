using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OSharp
{
    public interface ITerminal
    {
        bool CheckVisible { get; }
        bool CheckFocus { get; }
        void SetVisibility(bool visible);
    }
}