using LiteDB;

using MXLPersonalArmory.IPC.Messaging.Messages;

namespace MXLPersonalArmory.Database
{
    class InventoryRepository : Database
    {
        public static void UpdateInventory(Inventory inventory)
        {
            LiteCollection<Inventory> col = DB.GetCollection<Inventory>("inventory");
            col.Delete(inv => inv.characterName == inventory.characterName);
            col.Insert(inventory);
        }
    }
}
