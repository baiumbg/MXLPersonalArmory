using System.Collections.Generic;
using LiteDB;

using MXLPersonalArmory.IPC.Messaging.Messages.Models;
using MXLPersonalArmory.Globals;

namespace MXLPersonalArmory.IPC.Messaging.Messages
{
    class Inventory : MessageBody
    {
        public ObjectId id { get; set; } // Needed for LiteDB, not part of the message itself.
        public string characterName { get; set; }
        public List<Item> items { get; set; } = new List<Item>();

        override
        public string ToString() => "{\"characterName\" = \"" + characterName + "\", \"items\" = [" + Utils<Item>.ListToString(items) + "]}";
    }
}