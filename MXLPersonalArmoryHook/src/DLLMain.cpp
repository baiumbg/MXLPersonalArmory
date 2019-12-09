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
        if (!!D2CLIENT_GetPlayerUnit())
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