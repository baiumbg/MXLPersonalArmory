using System;
using LiteDB;

namespace MXLPersonalArmory.Database
{
    class Database
    {
        public static string DatabasePath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"\MXLPersonalArmory";
        protected static LiteDatabase DB = new LiteDatabase(DatabasePath + @"\Database.db");
    }
}
