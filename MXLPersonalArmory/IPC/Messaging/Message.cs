namespace MXLPersonalArmory.IPC.Messaging
{
    public class Message
    {
        public MessageType type { get; set; }
        public MessageBody body { get; set; }

        public Message(MessageType type_, MessageBody body_)
        {
            type = type_;
            body = body_;
        }

        override
        public string ToString() => "{\"type\" = " + (int)type + ", \"body\" = " + body.ToString() + "}";
    }
}