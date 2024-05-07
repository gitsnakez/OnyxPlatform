using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OSharp.Engine
{
    public static class Time
    {
        /// <summary>
        /// Time before frame(Before frame calculations)
        /// </summary>
        public static float PreviousTime { get; private set; }

        /// <summary>
        /// Time after frame(after frame calculations)
        /// </summary>
        public static float CurrentTime { get; private set; }

        /// <summary>
        /// Delta of time between frames(time of current frame calculations)
        /// </summary>
        public static float DeltaTime { get; private set; }
    }
}