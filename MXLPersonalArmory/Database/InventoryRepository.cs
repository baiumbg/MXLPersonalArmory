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
            Inventory existingInventory = GetInventory(inventory.characterName);
            if (existingInventory != null)
            {
                collection.Delete(existingInventory.id);
            }
            collection.Insert(inventory);
        }
    }
}
