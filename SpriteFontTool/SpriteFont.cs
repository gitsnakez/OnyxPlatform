using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpriteFontTool
{
    class SpriteFont
    {
        public string output_path;
        public string fontname;
        public float fontsize;
        public string style;
        public int linespacing;
        public bool sharp;
        public bool fastpack;
        public int[,] charRegions;

        public void ConvertLanguagesToRegions(string[] languages)
        {
            charRegions = new int[languages.Length, 2];
            for (int i = 0; i < languages.Length; i++)
            {
                switch (languages[i])
                {
                    case "Cyrillic":
                        charRegions[i, 0] = 0x0400;
                        charRegions[i, 1] = 0x04FF;
                    break;

                    case "Armenian":
                        charRegions[i, 0] = 0x0530;
                        charRegions[i, 1] = 0x058F;
                    break;

                    case "Hebrew":
                        charRegions[i, 0] = 0x0590;
                        charRegions[i, 1] = 0x05FF;
                    break;

                    case "Arabic":
                        charRegions[i, 0] = 0x0600;
                        charRegions[i, 1] = 0x06FF;
                    break;

                    case "Syriac":
                        charRegions[i, 0] = 0x0700;
                        charRegions[i, 1] = 0x073F;
                    break;

                    case "Thaana":
                        charRegions[i, 0] = 0x0780;
                        charRegions[i, 1] = 0x07BF;
                    break;

                    case "NKo":
                        charRegions[i, 0] = 0x07C0;
                        charRegions[i, 1] = 0x07FF;
                    break;

                    case "Samaritan":
                        charRegions[i, 0] = 0x0800;
                        charRegions[i, 1] = 0x083F;
                    break;

                    case "Mandaic":
                        charRegions[i, 0] = 0x0840;
                        charRegions[i, 1] = 0x085F;
                    break;
                }
            }
        }

        static public string MakeFont(SpriteFont font)
        {
            string command = string.Empty;

            command = $"\"{font.fontname}\" /FontSize:{font.fontsize} ";
            command += (font.fastpack) ?  "/FastPack " : "";
            command += (font.style != "Regular") ? $"/FontStyle:{font.style} " : "";
            command += (font.linespacing != 0) ? $"/LineSpacing:{font.linespacing} " : "";
            command += (font.sharp) ? "/Sharp " : "";

            if (font.charRegions.Length > 0)
            {
                command += "/CharacterRegion:0x0000-0x007F ";
                for(int i = 0; i < font.charRegions.Length / 2; i++)
                {
                    command += $"/CharacterRegion:0x0{font.charRegions[i, 0].ToString("X")}-0x0{font.charRegions[i, 1].ToString("X")} ";
                }
            }

            command += font.output_path;

            return command;
        }
    }
}