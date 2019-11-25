using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using System.IO.Pipes;

namespace MXLPersonalArmory
{
    public partial class MainWindow : Window
    {
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress,
            uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess,
            IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr CreateThread(IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        // privileges
        const int PROCESS_CREATE_THREAD = 0x0002;
        const int PROCESS_QUERY_INFORMATION = 0x0400;
        const int PROCESS_VM_OPERATION = 0x0008;
        const int PROCESS_VM_WRITE = 0x0020;
        const int PROCESS_VM_READ = 0x0010;

        // used for memory allocation
        const uint MEM_COMMIT = 0x00001000;
        const uint MEM_RESERVE = 0x00002000;
        const uint PAGE_READWRITE = 4;

        private const int SLEEP_BETWEEN_PROC_CHECK = 1000;

        Dictionary<int, NamedPipeServerStream> OpenProcesses = new Dictionary<int, NamedPipeServerStream>();

        public void Log(string message)
        {
            Debug.WriteLine(message);
            this.Dispatcher.Invoke(() => {
                logBox.Text += "\n " + message;
            });
        }

        private string ReadMessage(NamedPipeServerStream pipeServer, int  pId)
        {
            StreamReader sr = new StreamReader(pipeServer);
            string message = sr.ReadLine();
            Log("Received messaage from " + pId + ": " + message);
            return message;
        }

        private void PipeReaderThread(NamedPipeServerStream pipeServer, int pId)
        {
            while (pipeServer.IsConnected)
            {
                ReadMessage(pipeServer, pId);
            }
            OpenProcesses.Remove(pId);
            Log("Client " + pId + " has disconnected");
        }

        private void BackgroundInjector()
        {
            IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            string dllName = Path.Combine(Path.GetDirectoryName(Process.GetCurrentProcess().MainModule.FileName), "MXLPersonalArmoryHook.dll");
            while (true)
            {
                foreach (Process p in Process.GetProcessesByName("Game"))
                {
                    if (p.Threads.Count < 1 || OpenProcesses.ContainsKey(p.Id))
                    {
                        continue;
                    }

                    IntPtr procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, p.Id);
                    IntPtr allocMemAddress = VirtualAllocEx(procHandle, IntPtr.Zero, (uint)((dllName.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                    UIntPtr bytesWritten;
                    WriteProcessMemory(procHandle, allocMemAddress, Encoding.Default.GetBytes(dllName), (uint)((dllName.Length + 1) * Marshal.SizeOf(typeof(char))), out bytesWritten);
                    IntPtr RemoteThread = CreateRemoteThread(procHandle, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, IntPtr.Zero);

                    if(RemoteThread != null)
                    {
                        Log("Successfully attached to " + p.Id);
                        NamedPipeServerStream pipeServer = new NamedPipeServerStream("MXLPersonalArmoryHook", PipeDirection.InOut, NamedPipeServerStream.MaxAllowedServerInstances);
                        Log("Waiting for " + p.Id + " pipe connection...");
                        pipeServer.WaitForConnection();
                        Log("Client "+ p.Id + " has connected");
                        Thread pipeReaderThread = new Thread(() => PipeReaderThread(pipeServer, p.Id));
                        pipeReaderThread.Start();
                        OpenProcesses[p.Id] = pipeServer;
                    }
                    else
                    {
                        Log("Failed to attach to " + p.Id);
                    }
                }
                Thread.Sleep(SLEEP_BETWEEN_PROC_CHECK);
            }
        }

        public MainWindow()
        {
            InitializeComponent();
            Thread backgroundInjectorThread = new Thread(BackgroundInjector);
            backgroundInjectorThread.Start();
        }
    }
}
