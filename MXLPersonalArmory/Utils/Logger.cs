using System.Diagnostics;

namespace MXLPersonalArmory
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
