using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace Onyx
{
    static public class MessageSystem
    {
        public static bool? Show(string title, string message)
        {
            var dialog = new MessageWindow(title, message);
            return dialog.ShowDialog();
        }
    }
}
