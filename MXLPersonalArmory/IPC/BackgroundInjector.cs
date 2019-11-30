using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;
using System.Threading;
using System.Collections.Generic;

namespace MXLPersonalArmory
{
    class BackgroundInjector
    {
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr CreateThread(IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        HashSet<int> OpenProcesses = new HashSet<int>();

        private void PipeReaderThread(PipeClient pipeClient)
        {
            while (pipeClient.Pipe.IsConnected)
            {
                pipeClient.ReadMessage();
            }
            Logger.Log("Client " + pipeClient.PID + " has disconnected");
            OpenProcesses.Remove(pipeClient.PID);
        }

        private void BackgroundInjectorThread()
        {
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

            const int SLEEP_BETWEEN_PROC_CHECK = 1000;

            IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            string dllName = Path.Combine(Path.GetDirectoryName(Process.GetCurrentProcess().MainModule.FileName), "MXLPersonalArmoryHook.dll");

            while (true)
            {
                foreach (Process p in Process.GetProcessesByName("Game"))
                {
                    if (p.Threads.Count < 1 || OpenProcesses.Contains(p.Id))
                    {
                        continue;
                    }

                    IntPtr procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, p.Id);
                    IntPtr allocMemAddress = VirtualAllocEx(procHandle, IntPtr.Zero, (uint)((dllName.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                    UIntPtr bytesWritten;
                    WriteProcessMemory(procHandle, allocMemAddress, Encoding.Default.GetBytes(dllName), (uint)((dllName.Length + 1) * Marshal.SizeOf(typeof(char))), out bytesWritten);
                    PipeClient pipeClient = new PipeClient(p.Id);
                    IntPtr RemoteThread = CreateRemoteThread(procHandle, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, IntPtr.Zero);

                    if (RemoteThread != null)
                    {
                        Logger.Log("Waiting for " + p.Id + " pipe connection...");
                        pipeClient.Pipe.WaitForConnection();
                        Logger.Log("Client " + p.Id + " has connected");
                        Thread pipeReaderThread = new Thread(() => PipeReaderThread(pipeClient));
                        pipeReaderThread.IsBackground = true;
                        pipeReaderThread.Start();
                        OpenProcesses.Add(p.Id);
                        Logger.Log("Successfully attached to " + p.Id);
                    }
                    else
                    {
                        Logger.Log("Failed to attach to " + p.Id);
                        pipeClient.Pipe.Disconnect();
                    }
                    pipeClient.SendMessage("Test");
                }
                Thread.Sleep(SLEEP_BETWEEN_PROC_CHECK);
            }
        }

        public void Start()
        {
            Thread backgroundInjectorThread = new Thread(BackgroundInjectorThread);
            backgroundInjectorThread.IsBackground = true;
            backgroundInjectorThread.Start();
        }
    }
}
