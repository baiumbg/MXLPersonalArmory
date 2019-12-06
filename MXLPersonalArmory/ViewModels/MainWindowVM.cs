using System.ComponentModel;

namespace MXLPersonalArmory.ViewModels
{
    public class MainWindowVM: INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public string LogBox
        {
            get {
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
        private string logBox;
        private string cmdBox;

        private void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
