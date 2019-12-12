#include <Messages/InventoryMessage.h>

void InventoryMessage::serializeBody(rapidjson::WValue& body, rapidjson::WDocument::AllocatorType& allocator)
{
    body.AddMember(L"characterName", rapidjson::WValue().SetString(Character.c_str(), Character.length(), allocator), allocator);
    
    rapidjson::WValue items;
    items.SetArray();

    for (auto& item : Items)
    {
        rapidjson::WValue itemJSON;
        itemJSON.SetObject();

        itemJSON.AddMember(L"location", item.location, allocator);
        itemJSON.AddMember(L"locX", rapidjson::WValue().SetUint64(item.locX), allocator);
        itemJSON.AddMember(L"locY", rapidjson::WValue().SetUint64(item.locY), allocator);
        itemJSON.AddMember(L"name", rapidjson::WValue().SetString(item.name.c_str(), item.name.length(), allocator), allocator);
        itemJSON.AddMember(L"type", rapidjson::WValue().SetUint64(item.type), allocator);

        rapidjson::WValue itemStatsJSON;
        itemStatsJSON.SetArray();
        for (auto& stat : item.stats)
        {
            rapidjson::WValue statJSON;
            statJSON.SetObject();

            statJSON.AddMember(L"id", stat.id, allocator);
            statJSON.AddMember(L"value", rapidjson::WValue().SetUint64(stat.value), allocator);
            statJSON.AddMember(L"subId", stat.subId, allocator);

            itemStatsJSON.PushBack(statJSON, allocator);
        }

        itemJSON.AddMember(L"stats", itemStatsJSON, allocator);
        items.PushBack(itemJSON, allocator);
    }

    body.AddMember(L"items", items, allocator);
}