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
        private string logBox;

        private void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
