using System.Collections.Generic;

using MXLPersonalArmory.IPC.Messaging.Messages.Models;
using MXLPersonalArmory.Globals;

namespace MXLPersonalArmory.IPC.Messaging.Messages
{
    class InventoryMessage : MessageBody
    {
        public string characterName { get; set; }
        public List<Item> items { get; set; } = new List<Item>();

        override
        public string ToString() => "{\"characterName\" = \"" + characterName + "\", \"items\" = [" + Utils<Item>.ListToString(items) + "]}";
    }
}