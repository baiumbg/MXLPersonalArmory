using System.Windows;

using MXLPersonalArmory.ViewModels;

namespace MXLPersonalArmory
{
    public partial class MainWindow : Window
    {
        public static MainWindowVM ViewModel { get; } = new MainWindowVM();

        public MainWindow()
        {
            InitializeComponent();
            DataContext = ViewModel;
        }

        private void SendCommand(object sender, RoutedEventArgs e)
        {
            ViewModel.SendCommand();
        }
    }
}
