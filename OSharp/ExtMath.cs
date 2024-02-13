using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OSharp
{
    static public class ExtMath
    {
        /// <summary>
        /// Linear intERpolation
        /// </summary>
        /// <param name="startf">Start float</param>
        /// <param name="endf">Desierd float</param>
        /// <param name="delta">Frame delta time</param>
        /// <returns>Intermediate value between start and final values.</returns>
        static public float Lerp(float startf, float endf, float delta)
	    {
		    return startf * (1.0f - delta) + endf * (delta);
        }
    }
}
