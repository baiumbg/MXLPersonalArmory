namespace MXLPersonalArmory.IPC.Messaging.Messages.Models
{
    class Stat
    {
        public int id { get; set; }
        public int value { get; set; }
        public int subId { get; set; }

        override
        public string ToString() => "{\"id\" = " + id + ", \"value\" = " + value + ", \"subId\" = " + "}";
    }
}