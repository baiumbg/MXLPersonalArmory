#include <windows.h>
#include <D2Ptrs.h>
#include <PipeClient.h>
#include "MPQStats.h"

#include <sstream>

DWORD WINAPI D2Thread(LPVOID lpParam)
{
    HMODULE mxlpaModule = (HMODULE)lpParam;

    if (!!D2CLIENT_GetPlayerUnit())
    {
        D2CLIENT_Print(L"You son of a bitch. I'm in.", 0);
    }

    g_PipeClient.send(L"You son of a bitch. I'm in.");

    std::wstring msg;
    while (g_PipeClient.read(msg) && msg != L"exit")
    {
        if (msg == L"debug" && !!D2CLIENT_GetPlayerUnit())
        {
            StatList* stats = D2COMMON_GetStatList(D2CLIENT_GetPlayerUnit()->pInventory->pCursorItem, 0, 64);
            Stat allStats[256] = { NULL };
            DWORD numberOfStats = D2COMMON_CopyStatList(stats, (Stat*)allStats, 256);
            for (DWORD i = 0; i < numberOfStats; ++i)
            {
                WORD result;
                FillBaseStat("itemstatcost", allStats[i].wStatIndex, "descstrpos", &result, sizeof(WORD));

                if (result != 5382)
                {
                    std::wstringstream s;
                    s << L"+" << (allStats[i].wStatIndex > 6 && allStats[i].wStatIndex < 11 ? allStats[i].dwStatValue >> 8 : allStats[i].dwStatValue) << L' ' << D2LANG_GetLocaleText(result) << L' ' << result << L' ' << allStats[i].wStatIndex;
                    D2CLIENT_Print(s.str().c_str(), 0);
                }
            }
        }
        else
        {
            D2CLIENT_Print(msg.c_str(), 0);
        }
    }

    FreeLibraryAndExitThread(mxlpaModule, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        g_PipeClient.connect();
        CreateThread(NULL, 0, D2Thread, hinstDLL, 0, NULL);
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        g_PipeClient.disconnect();
        break;
    }
    }

    return TRUE;
}