#include <windows.h>
#include <D2Ptrs.h>
#include <PipeClient.h>

#include <sstream>

DWORD WINAPI D2Thread(LPVOID lpParam)
{
    HMODULE mxlpaModule = (HMODULE)lpParam;

    while (!D2CLIENT_GetPlayerUnit())
    {
        Sleep(200);
    }

    std::wstringstream s;
    s << D2CLIENT_GetPlayerUnit()->pPlayerData->szName << L" is in the house.";

    g_PipeClient.send(s.str());
    D2CLIENT_Print(s.str().c_str(), 0);

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
        g_PipeClient.disconnect();
        break;
    }

    return TRUE;
}