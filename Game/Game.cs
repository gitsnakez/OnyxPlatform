using OSharp.Engine;
using OSharp.Steamworks;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game
{
    public static class Game
    {
        /// <summary>
        /// This is AppID of Onyx SDK
        /// </summary>
        internal const uint AppID = 2872880;


        public static void Main()
        {
            using (Steam steam = new Steam(AppID))
            {
                Achievements.UnlockAchievement("ACH_FIRST_START");
            }
        }
    }
}
