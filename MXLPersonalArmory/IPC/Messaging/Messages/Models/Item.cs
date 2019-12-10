using System.Collections.Generic;

using MXLPersonalArmory.Globals;

namespace MXLPersonalArmory.IPC.Messaging.Messages.Models
{
    class Item
    {
        public int location { get; set; }
        public int locX { get; set; }
        public int locY { get; set; }
        public string name { get; set; }
        public int type { get; set; }
        public List<Stat> stats { get; set; } = new List<Stat>();

        override
        public string ToString() => "{\"location\" = " + location + ", \"locX\" = " + locX + ", \"locY\" = " + locY + 
                                    ", \"name\" = \"" + name + "\", \"type\" = " + type + ", \"stats\" = [" + Utils<Stat>.ListToString(stats) + "]}";
    }
}