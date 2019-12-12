#include <D2Helpers.h>
#include <D2Ptrs.h>
#include <MPQStats.h>
#include <D2Constants.h>

#include <regex>

static const std::wregex ITEM_COLOR_REGEX(L"\u00ffc.");

DWORD __declspec(naked) __fastcall D2CLIENT_GetUIVar_STUB(DWORD varno)
{
    __asm
    {
        mov eax, ecx;
        jmp D2CLIENT_GetUiVar_I;
    }
}

namespace MXLPA
{
void CollectItems(std::vector<Item>& items)
{
    if (!D2CLIENT_GetPlayerUnit())
    {
        return;
    }

    auto item = D2CLIENT_GetPlayerUnit()->pInventory->pFirstItem;
    while (item != nullptr)
    {
        wchar_t buf[128] = L"";
        D2CLIENT_GetItemName(item, buf, 128);
        std::wstring name(buf, wcslen(buf));

        Item i;
        i.locX = item->pItemData->BodyLocation == 0 ? item->pItemPath->dwPosX % 4 : item->pItemPath->dwPosX;
        i.locY = item->pItemData->BodyLocation == 0 ? item->pItemPath->dwPosX / 4 : item->pItemPath->dwPosY;
        i.type = item->pItemData->dwQuality;
        i.name = std::regex_replace(name, ITEM_COLOR_REGEX, L"");

        switch (item->pItemData->ItemLocation)
        {
        case (BYTE)D2ItemLocation::Inventory:
        {
            i.location = (BYTE)ItemLocation::Inventory;
            break;
        }
        case (BYTE)D2ItemLocation::Cube:
        {
            i.location = (BYTE)ItemLocation::Cube;
            break;
        }
        case (BYTE)D2ItemLocation::Stash:
        {
            i.location = (BYTE)ItemLocation::Stash;
            break;
        }
        case (BYTE)D2ItemLocation::Equipped:
        {
            i.location = item->pItemData->BodyLocation == 0 ? (BYTE)ItemLocation::Belt : (BYTE)ItemLocation::Equipped;
            break;
        }
        }

        StatList* statList = D2COMMON_GetStatList(item, 0, 64);
        ::Stat allStats[256] = { NULL };
        DWORD numberOfStats = D2COMMON_CopyStatList(statList, (::Stat*)allStats, 256);
        for (DWORD it = 0; it < numberOfStats; ++it)
        {
            WORD txtRecord;
            FillBaseStat("itemstatcost", allStats[it].wStatIndex, "descstrpos", &txtRecord, sizeof(WORD));

            if (txtRecord != 5382)
            {
                i.stats.push_back({ allStats[it].wStatIndex, allStats[it].wStatIndex > 6 && allStats[it].wStatIndex < 11 ? allStats[it].dwStatValue >> 8 : allStats[it].dwStatValue, allStats[it].wSubIndex });
            }
        }

        items.push_back(i);

        item = item->pItemData->pNextInvItem;
    }

}
}