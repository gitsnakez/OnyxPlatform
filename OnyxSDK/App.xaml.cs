using OSharp.Steamworks;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.IO;
using System.Linq;
using System.Security;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Threading;

namespace OnyxSDK
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static IntPtr oldHWin;
        public static IntPtr hWin;

        [STAThread]
        public static int Main(string[] args)
        {
            Directory.SetCurrentDirectory(Regex.Replace(Directory.GetCurrentDirectory(), @"bin/$", ""));
#if _Steam
            //if (Steam.SteamAPI_RestartAppIfNecessary(2973920)) return 1;

            using (Steam steamApi = new Steam(2973920))
            {
                var application = new App();
                application.InitializeComponent();
                application.Run();
            }
#else
            var application = new App();
            application.InitializeComponent();

            
            //var th = new Thread(() =>
            //{
            //    oldHWin = OAPI.CreateRenderWindowBorderless();
            //    hWin = oldHWin;
            //    OAPI.RunWithGraphics(hWin);
            //});
            //th.SetApartmentState(ApartmentState.STA);
            //th.Start();

            application.Run();
#endif
            return 0;
        }
    }
}