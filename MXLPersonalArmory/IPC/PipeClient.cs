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
            byte[] c = new byte[1024];
            int len = Pipe.Read(c, 0, c.Length);
            string message = Encoding.Unicode.GetString(c, 0, len);
            Logger.Log("Received message from " + PID + ": " + message);
            return message;
        }

        public void SendMessage(string message)
        {
            byte[] c = Encoding.Unicode.GetBytes(message);
            Pipe.Write(c, 0, c.Length);
            Logger.Log("Sent message to " + PID + ": " + message);
        }
    }
}