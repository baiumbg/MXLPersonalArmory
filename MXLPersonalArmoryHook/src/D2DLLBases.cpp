#include <windows.h>

extern const DWORD DLLBASE_BNCLIENT     = (DWORD)LoadLibraryA("Bnclient.dll");
extern const DWORD DLLBASE_D2CLIENT     = (DWORD)LoadLibraryA("D2Client.dll");
extern const DWORD DLLBASE_D2CMP        = (DWORD)LoadLibraryA("D2CMP.dll");
extern const DWORD DLLBASE_D2COMMON     = (DWORD)LoadLibraryA("D2Common.dll");
extern const DWORD DLLBASE_D2DDRAW      = (DWORD)LoadLibraryA("D2DDraw.dll");
extern const DWORD DLLBASE_D2DIRECT3D   = (DWORD)LoadLibraryA("D2Direct3D.dll");
extern const DWORD DLLBASE_D2GAME       = (DWORD)LoadLibraryA("D2Game.dll");
extern const DWORD DLLBASE_D2GDI        = (DWORD)LoadLibraryA("D2Gdi.dll");
extern const DWORD DLLBASE_D2GFX        = (DWORD)LoadLibraryA("D2Gfx.dll");
extern const DWORD DLLBASE_D2GLIDE      = (DWORD)LoadLibraryA("D2Glide.dll");
extern const DWORD DLLBASE_D2LANG       = (DWORD)LoadLibraryA("D2Lang.dll");
extern const DWORD DLLBASE_D2LAUNCH     = (DWORD)LoadLibraryA("D2Launch.dll");
extern const DWORD DLLBASE_D2MCPCLIENT  = (DWORD)LoadLibraryA("D2MCPClient.dll");
extern const DWORD DLLBASE_D2MULTI      = (DWORD)LoadLibraryA("D2Multi.dll");
extern const DWORD DLLBASE_D2NET        = (DWORD)LoadLibraryA("D2Net.dll");
extern const DWORD DLLBASE_D2SOUND      = (DWORD)LoadLibraryA("D2Sound.dll");
extern const DWORD DLLBASE_D2WIN        = (DWORD)LoadLibraryA("D2Win.dll");
extern const DWORD DLLBASE_FOG          = (DWORD)LoadLibraryA("Fog.dll");
extern const DWORD DLLBASE_STORM        = (DWORD)LoadLibraryA("Storm.dll");
extern const DWORD DLLBASE_IJL11        = (DWORD)LoadLibraryA("ijl11.dll");
extern const DWORD DLLBASE_BINKW32      = (DWORD)LoadLibraryA("binkw32.dll");
extern const DWORD DLLBASE_SMACKW32     = (DWORD)LoadLibraryA("SmackW32.dll");

DWORD __fastcall GetDllOffset(const char* ModuleName, DWORD BaseAddress, int Offset)
{
    char DLLExt[] = ".dll";
    char DLLName[32] = { 0 };
    strcpy_s(DLLName, ModuleName);
    strcat_s(DLLName, DLLExt);

    if (!BaseAddress)
        BaseAddress = (DWORD)LoadLibraryA(DLLName);

    if (Offset < 0)
        return (DWORD)GetProcAddress((HMODULE)BaseAddress, (LPCSTR)(-Offset));

    return BaseAddress + Offset;
}