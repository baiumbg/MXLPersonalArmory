#pragma once

#include <Windows.h>
#include <vector>
#include <string>

DWORD __fastcall D2CLIENT_GetUIVar_STUB(DWORD varno);

namespace MXLPA
{

struct Stat
{
    WORD id;
    DWORD value;
    WORD subId;
};

struct Item
{
    BYTE location = 0;
    DWORD locX = 0;
    DWORD locY = 0;
    std::wstring name;
    DWORD type = 0;
    std::vector<Stat> stats;
};

void CollectItems(std::vector<MXLPA::Item>& items);

}