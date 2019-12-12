#pragma once

#include <vector>

#include <Messages/BaseMessage.h>
#include <D2Helpers.h>

struct InventoryMessage : public BaseMessage
{
    InventoryMessage() : BaseMessage(MessageType::Inventory) {}

    std::wstring Character;
    std::vector<MXLPA::Item> Items;

private:
    void serializeBody(rapidjson::WValue& body, rapidjson::WDocument::AllocatorType& allocator) override;
};