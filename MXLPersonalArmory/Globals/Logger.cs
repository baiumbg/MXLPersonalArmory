using System.Diagnostics;

namespace MXLPersonalArmory.Globals
{
    class Logger
    {
        public static void Log(string text)
        {
            MainWindow.ViewModel.LogBox += text + "\n";
            Debug.WriteLine(text);
        }
    }
}
