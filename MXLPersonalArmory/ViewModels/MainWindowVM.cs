using System.Collections.Generic;
using System.ComponentModel;

namespace MXLPersonalArmory.ViewModels
{
    public class MainWindowVM: INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public string LogBox
        {
            get
            {
                return logBox;
            }
            set
            {
                logBox = value;
                OnPropertyChanged("LogBox");
            }
        }

        public string CommandBox
        {
            get
            {
                return cmdBox;
            }
            set
            {
                cmdBox = value;
                OnPropertyChanged("CommandBox");
            }
        }

        public MainWindowVM()
        {
            backgroundInjector = new BackgroundInjector();
            backgroundInjector.Start();
        }

        public void SendCommand()
        {
            foreach (KeyValuePair<int, PipeClient> entry in backgroundInjector.OpenProcesses)
            {
                entry.Value.SendMessage(CommandBox);
            }

            CommandBox = "";
        }

        private void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        private BackgroundInjector backgroundInjector;
        private string logBox;
        private string cmdBox;
    }
}
