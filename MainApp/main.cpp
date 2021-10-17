#include <iostream>
#include <windows.h>
#include <stdint.h>
#include <chrono>
#include <thread>

#define SIGNATURE_OF_FUNC(functionName) int functionName()
typedef SIGNATURE_OF_FUNC(funcType);
SIGNATURE_OF_FUNC(funcStub)
{
    std::cout << "This is just a stub, this shouldn't run" << std::endl;
    return 0;
}
static funcType *exampleFunc = funcStub;

// TODO: erase signatures
#define SIGNATURE_OF_CBK(name) int name()
typedef SIGNATURE_OF_CBK(cbk);
SIGNATURE_OF_CBK(callbackFunction)
{
    std::cout << "I am the callback function" << std::endl;
    return 0;
}

#define SIGNATURE_OF_SET_CBK(functionName) int functionName(cbk *)
typedef SIGNATURE_OF_SET_CBK(setCbkType);
SIGNATURE_OF_SET_CBK(setCbkStub)
{
    std::cout << "This is just a stub, this shouldn't run" << std::endl;
    return 0;
}
static setCbkType *setCbk = setCbkStub;

#define SIGNATURE_OF_RUN_ALL_CALLBACKS(functionName) int functionName()
typedef SIGNATURE_OF_RUN_ALL_CALLBACKS(runAllCallbacksType);
SIGNATURE_OF_RUN_ALL_CALLBACKS(runAllCallbacksStub)
{
    std::cout << "This is just a stub, this shouldn't run" << std::endl;
    return 0;
}
static runAllCallbacksType *runAllCallbacks = runAllCallbacksStub;

HMODULE libModule = nullptr;
int loadLibrary(std::string& path) {
    // TODO: check file changes
    if (libModule != nullptr) {
        std::cout << "Library was already loaded" << std::endl;
        return 0;
    }
    // TODO: free the library if it exists
    // TODO: create a working copy of the library
    // load the dll

    libModule = LoadLibraryA(path.c_str());
    if (!libModule)
    {
        uint32_t errorCode = GetLastError();
        if (errorCode == 126)
        {
            std::cout << "Couldn't load library with error code 126, are you sure you built it?" << std::endl;
        }
        else
        {
            std::cout << "Couldn't load the library with error code " << errorCode << std::endl;
        }
        return 0;
    }

    // load and call a function from the dll
    exampleFunc = reinterpret_cast<funcType*>(GetProcAddress(libModule, "exampleFunc"));
    if (!exampleFunc)
    {
        std::cout << "Couldn't load the dll function "
            << "exampleFunc"
            << " with error code " << GetLastError() << std::endl;
        return 0;
    }
    exampleFunc();

    // pass a callback function to the dll
    setCbk = reinterpret_cast<setCbkType*>(GetProcAddress(libModule, "setCbk"));
    if (!setCbk)
    {
        std::cout << "Couldn't give callback "
            << "cbk"
            << " to the dll with error code " << GetLastError() << std::endl;
        return 0;
    }
    setCbk(callbackFunction);

    // run all callbacks in the dll
    runAllCallbacks = reinterpret_cast<runAllCallbacksType*>(GetProcAddress(libModule, "runAllCallbacks"));
    if (!runAllCallbacks)
    {
        std::cout << "Couldn't load the dll function "
            << "runAllCallbacks"
            << " with error code " << GetLastError() << std::endl;
        return 0;
    }
    runAllCallbacks();

    // TODO: ensure a temp folder exists
    return 1;
}
int main()
{
    std::string pathToLibrary = std::string("../../../SharedCode/bin/Debug/SharedCode.dll");
    std::cout << "Hello. I am the main app, the god of all the libraries" << std::endl;
    loadLibrary(pathToLibrary);
    for (;;){
        std::cout << "Tick!" << std::endl;
        loadLibrary(pathToLibrary);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}