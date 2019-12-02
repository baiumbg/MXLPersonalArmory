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
            BackgroundInjector backgroundInjector = new BackgroundInjector();
            backgroundInjector.Start();
        }
    }
}
