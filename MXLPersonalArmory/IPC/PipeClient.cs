using System.IO.Pipes;
using System.Text;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

using MXLPersonalArmory.IPC.Messaging;
using MXLPersonalArmory.IPC.Messaging.Messages;
using Logger = MXLPersonalArmory.Globals.Logger;
using MXLPersonalArmory.Database;

namespace MXLPersonalArmory
{
    public class PipeClient
    {
        public NamedPipeServerStream Pipe { get; }
        public int PID { get; }

        public PipeClient(int _pId)
        {
            Pipe = new NamedPipeServerStream("MXLPersonalArmoryHook", PipeDirection.InOut, NamedPipeServerStream.MaxAllowedServerInstances, PipeTransmissionMode.Message);
            PID = _pId;
        }

        public void HandleMessage(Message message)
        {
            switch (message.type)
            {
                case MessageType.Inventory:
                    Logger.Log(message.ToString());
                    InventoryRepository.UpdateInventory((Inventory)message.body);
                    break;
            }
        }

        private Message ParseMessage(string json)
        {
            JObject o = JObject.Parse(json);
            MessageType messageType = (MessageType)(int)o["type"];
            MessageBody messageBody = null;

            switch (messageType)
            {
                case MessageType.Inventory:
                    {
                        messageBody = o["body"].ToObject<Inventory>();
                        break;
                    }
            }
            return new Message(messageType, messageBody);
        }

        public Message ReadMessage()
        {
            byte[] c = new byte[80960];
            int len = Pipe.Read(c, 0, c.Length);
            string messageString = Encoding.Unicode.GetString(c, 0, len);
            Message message = ParseMessage(messageString);
            Logger.Log("Received message from " + PID + ": " + messageString);
            return message;
        }

        public void SendMessage(string message)
        {
            byte[] c = Encoding.Unicode.GetBytes(message);
            Pipe.Write(c, 0, c.Length);
            Logger.Log("Sent message to " + PID + ": " + message);
        }

        public void SendMessage(Message message)
        {
            string json = JsonConvert.SerializeObject(message);
            byte[] c = Encoding.Unicode.GetBytes(json);
            Pipe.Write(c, 0, c.Length);
            Logger.Log("Sent message to " + PID + ": " + json);
        }
    }
}