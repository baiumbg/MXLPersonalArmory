using LiteDB;

namespace MXLPersonalArmory.Database
{
    class Database
    {
        public static string DatabasePath = @"C:\Users\" + System.Environment.UserName + @"\AppData\Local\MXLPersonalArmory";
        protected static LiteDatabase DB = new LiteDatabase(DatabasePath + @"\Database.db");
    }
}
