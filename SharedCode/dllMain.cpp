#include <windows.h>
#include <iostream>

#define SIGNATURE_OF_CBK(name) int name()
typedef SIGNATURE_OF_CBK(cbk);
SIGNATURE_OF_CBK(cbkStub)
{
    std::cout << "This is just a stub, this shouldn't run" << std::endl;
    return 0;
}
static cbk *callback = cbkStub;
extern "C"
{
    __declspec(dllexport) int exampleFunc()
    {
        std::cout << "I am a procedure. I was loaded from the dll and I call it mommy." << std::endl;
        return 1;
    }
    __declspec(dllexport) int setCbk(cbk *arg)
    {
        callback = arg;
        return 1;
    }
    __declspec(dllexport) int runAllCallbacks()
    {
        callback();
        return 1;
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
        std::cout << "I am the dll. I am more loaded than the Kenyan president and women love me." << std::endl;
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