using LiteDB;

using MXLPersonalArmory.IPC.Messaging.Messages;

namespace MXLPersonalArmory.Database
{
    class InventoryRepository : Database
    {
        public static Inventory GetInventory(string characterName)
        {
            LiteCollection<Inventory> collection = DB.GetCollection<Inventory>("inventory");
            return collection.FindOne(inv => inv.characterName == characterName);
        }

        public static void UpdateInventory(Inventory inventory)
        {
            LiteCollection<Inventory> collection = DB.GetCollection<Inventory>("inventory");
            if (GetInventory(inventory.characterName) != null)
            {
                collection.Delete(inv => inv.characterName == inventory.characterName);
            }
            collection.Insert(inventory);
        }
    }
}
