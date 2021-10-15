#include <windows.h>
#include <iostream>
extern "C"
{
    __declspec(dllexport) int exampleFunc()
    {
        std::cout << "I am a procedure. I was loaded from the Dll and I call it mommy." << std::endl;
        return 0;
    }
}
BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        std::cout << "I am the dll and I am more loaded than the Kenyan president." << std::endl;
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        std::cout << "I am the dll and I am being unloaded, send help." << std::endl;
        break;
    }
    return TRUE;
}