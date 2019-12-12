#pragma once

#include <Windows.h>

#define UI_CHAT_CONSOLE     0x05
#define UI_ESCMENU_MAIN     0x09

enum class D2ItemLocation : BYTE
{
    Inventory = 0,
    Cube = 3,
    Stash = 4,
    Equipped = 255
};

enum class D2EquippedLocation : BYTE
{
    Helmet = 1,
    Amulet = 2,
    Body = 3,
    LeftWeapon = 4,
    RightWeapon = 5,
    LeftRing = 6,
    RightRing = 7,
    Belt = 8,
    Boots = 9,
    Gloves = 10,
    SwapLeftWeapon = 11,
    SwapRightWeapon = 12
};

enum class ItemLocation : BYTE
{
    Inventory = 0,
    Cube = 1,
    Stash = 2,
    Equipped = 3,
    Belt = 4
};