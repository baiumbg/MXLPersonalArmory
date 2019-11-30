using System.IO;
using System.IO.Pipes;
using System.Text;

namespace MXLPersonalArmory
{
    public class PipeClient
    {
        public NamedPipeServerStream Pipe { get; }
        public int PID { get; }

        public PipeClient(int _pId)
        {
            Pipe = new NamedPipeServerStream("MXLPersonalArmoryHook", PipeDirection.InOut, NamedPipeServerStream.MaxAllowedServerInstances, PipeTransmissionMode.Message, PipeOptions.Asynchronous);
            PID = _pId;
        }

        public string ReadMessage()
        {
            StreamReader sr = new StreamReader(Pipe);
            char[] c = new char[1024];
            int len = sr.Read(c, 0, c.Length);
            byte[] utf8Bytes = Encoding.UTF8.GetBytes(c);
            string message = Encoding.Unicode.GetString(utf8Bytes, 0, len);
            Logger.Log("Received messaage from " + PID + ": " + message);
            return message;
        }

        public void SendMessage(string message)
        {
            StreamWriter sw = new StreamWriter(Pipe);
            byte[] utf8Bytes = Encoding.Unicode.GetBytes(message);
            char[] convertedMessage = Encoding.UTF8.GetChars(utf8Bytes);
            sw.Write(convertedMessage);
            sw.Flush();
            Logger.Log("Sent messaage to " + PID + ": " + message);
        }
    }
}