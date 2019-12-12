#include <D2Ptrs.h>
#include <D2Hooks.h>
#include <D2Constants.h>
#include <D2Helpers.h>
#include <PipeClient.h>
#include <Messages/InventoryMessage.h>

#include <sstream>

#ifndef NDEBUG

HHOOK g_KeyHook = nullptr;

LRESULT CALLBACK KeyPress(int code, WPARAM wParam, LPARAM lParam)
{
    if (code < HC_ACTION)
    {
        return CallNextHookEx(NULL, code, wParam, lParam);
    }

    WORD repeatCount = LOWORD(lParam);
    bool altState = !!(HIWORD(lParam) & KF_ALTDOWN);
    bool previousState = !!(HIWORD(lParam) & KF_REPEAT);
    bool transitionState = !!(HIWORD(lParam) & KF_UP);
    bool isRepeat = !transitionState && repeatCount != 1;
    bool isDown = !(previousState && transitionState);
    bool isUp = previousState && transitionState;

    bool ingame = !!D2CLIENT_GetPlayerUnit();
    bool chatBoxOpen = ingame ? !!D2CLIENT_GetUIState(UI_CHAT_CONSOLE) : false;
    bool escMenuOpen = ingame ? !!D2CLIENT_GetUIState(UI_ESCMENU_MAIN) : false;

    // G
    if (wParam == 0x47)
    {
        if (ingame && !chatBoxOpen && !escMenuOpen && isUp && !isRepeat && code == HC_ACTION)
        {
            InventoryMessage msg;

            size_t nameLength = strlen(D2CLIENT_GetPlayerUnit()->pPlayerData->szName);
            msg.Character.resize(nameLength);
            mbstowcs(&msg.Character[0], D2CLIENT_GetPlayerUnit()->pPlayerData->szName, nameLength);

            MXLPA::CollectItems(msg.Items);

            g_PipeClient.send(msg.toJSONString());
        }
    }

    return CallNextHookEx(NULL, code, wParam, lParam);
}

// Do not call on main thread
bool InitHooks()
{
    int attempts = 0;
    while (attempts < 100)
    {
        DWORD mainThread = GetWindowThreadProcessId(D2GFX_GetHwnd(), 0);
        if (mainThread)
        {
            g_KeyHook = SetWindowsHookEx(WH_KEYBOARD, KeyPress, NULL, mainThread);
        }

        if (g_KeyHook)
        {
            return true;
        }

        ++attempts;
        Sleep(100);
    }

    return false;
}

bool DeinitHooks()
{
    if (g_KeyHook)
    {
        UnhookWindowsHookEx(g_KeyHook);
    }

    return true;
}


#else

bool InitHooks()
{
    return true;
}

bool DeinitHooks()
{
    return true;
}

#endif