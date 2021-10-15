#include <windows.h>
#include <iostream>
extern "C" {
    __declspec(dllexport) int exampleFunc()
    {
        std::cout << "and I am a procedure loaded from my wealthy parent, Mr. Dll" << std::endl;
        return 0;
    }
}
BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpvReserved)
{
    std::cout << "I am the dll and I am more loaded than the Kenyan president." << std::endl;
    return TRUE;
}