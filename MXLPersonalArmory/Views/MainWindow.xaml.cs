using System.Collections.Generic;
using System.Windows;

using MXLPersonalArmory.ViewModels;

namespace MXLPersonalArmory
{
    public partial class MainWindow : Window
    {
        private BackgroundInjector backgroundInjector;

        public static MainWindowVM ViewModel { get; } = new MainWindowVM();

        public MainWindow()
        {
            InitializeComponent();
            DataContext = ViewModel;
            backgroundInjector = new BackgroundInjector();
            backgroundInjector.Start();
        }

        private void SendCommand(object sender, RoutedEventArgs e)
        {
            foreach (KeyValuePair<int, PipeClient> entry in backgroundInjector.OpenProcesses)
            {
                entry.Value.SendMessage(ViewModel.CommandBox);
            }
        }
    }
}
