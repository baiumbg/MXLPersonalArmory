#include <windows.h>
#include <D2Ptrs.h>
#include <D2Hooks.h>
#include <PipeClient.h>

#include <sstream>

DWORD WINAPI D2Thread(LPVOID lpParam)
{
    HMODULE mxlpaModule = (HMODULE)lpParam;

    InitHooks();

    if (!!D2CLIENT_GetPlayerUnit())
    {
        D2CLIENT_Print(L"You son of a bitch. I'm in.", 0);
    }

    std::wstring msg;
    while (g_PipeClient.read(msg) && msg != L"exit")
    {
        if (!!D2CLIENT_GetPlayerUnit() && !msg.empty())
        {
            D2CLIENT_Print(msg.c_str(), 0);
        }

        Sleep(20);
    }

    D2CLIENT_Print(L"Bye Bye", 0);

    DeinitHooks();

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