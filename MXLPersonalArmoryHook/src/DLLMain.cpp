#include <windows.h>
#include <D2Ptrs.h>

DWORD WINAPI D2Thread(LPVOID lpParam)
{
    HMODULE mxlpaModule = (HMODULE)lpParam;
    D2CLIENT_Print((wchar_t*)L"I'm in.", 0);
    FreeLibraryAndExitThread(mxlpaModule, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(NULL, 0, D2Thread, hinstDLL, 0, NULL);
    }
    }

    return TRUE;
}