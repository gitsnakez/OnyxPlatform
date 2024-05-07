using OSharp.Standard;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OSharp.Steamworks
{
    #region Steam
    enum SteamInitResult
    {
        OK = 0,
        FailedGeneric = 1, // Some other failure
        NoSteamClient = 2, // We cannot connect to Steam, steam probably isn't running
        VersionMismatch = 3, // Steam client appears to be out of date
    }

    public sealed class Steam : IDisposable
    {
        private static bool IsInited = false;
        public uint AppID { get; private set; }

        [DllImport("steam_api64.dll", CallingConvention = CallingConvention.Cdecl)]
        static private extern SteamInitResult SteamAPI_InitFlat(char[] pOutErrMsg);

        [DllImport("steam_api64.dll", CallingConvention = CallingConvention.Cdecl)]
        static private extern bool SteamAPI_Shutdown();

        [DllImport("steam_api64.dll", CallingConvention = CallingConvention.Cdecl)]
        static public extern bool SteamAPI_RestartAppIfNecessary(uint unOwnAppID);

        public Steam(uint appID)
        {
            char[] msg = new char[1024];
            if (SteamInitResult.OK != SteamAPI_InitFlat(msg))
            { throw new Exception("Steam isn't initialized or steam account isn't signed in!"); }
                if (appID == 0) { throw new Exception("Bad steam appid!"); }
            AppID = AppID;
            if (IsInited == true) { throw new Exception("Steam api already initialized!"); }
            IsInited = true;
        }

        public static bool IsInitialized()
        {
            return IsInited;
        }

        public void Dispose()
        {
            if (!SteamAPI_Shutdown()) { throw new Exception("Steam release resources failed!"); }
            IsInited = false;
        }
    }
    #endregion
    #region Achievements
    public enum AchievementStatus
    {
        Unlocked,
        Locked,
    }

    public static class Achievements
    {
        private static bool isStatisticsGot = false;

        private static void CheckForStatistics()
        {
            if (!Steam.IsInitialized())
                throw new Exception("Steam isn't initialized or steam account isn't signed in!");

            if (!isStatisticsGot)
            {
                ///
                ///  NOT IMPLEMENTED!
                ///
            }

            isStatisticsGot = true;
        }

        public static AchievementStatus GetAchievement(string AchievementKey)
        {
            if (!Steam.IsInitialized())
                throw new Exception("Steam isn't initialized or steam account isn't signed in!");

            CheckForStatistics();

            ///
            ///  NOT IMPLEMENTED!
            ///

            return AchievementStatus.Unlocked;
        }

        public static Result UnlockAchievement(string AchievementKey)
        {
            if (!Steam.IsInitialized())
                throw new Exception("Steam isn't initialized or steam account isn't signed in!");

            CheckForStatistics();

            ///
            ///  NOT IMPLEMENTED!
            ///

            return Result.OK;
        }
    }
    #endregion

    #region RichStatuses
    public static class RichStatus
    {
        public static void SetParameter(string paramName, string paramValue)
        {

        }

        public static void SetParameter(string paramName, object paramValue)
        {

        }

        public static void SetStatus(string paramValue)
        {

        }
    }
    #endregion
}