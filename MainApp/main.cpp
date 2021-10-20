#include <iostream>
#include <windows.h>
#include <stdint.h>
#include <chrono>
#include <thread>
#include <filesystem>
namespace fs = std::filesystem;

#define SIGNATURE_OF_FUNC(functionName) int32_t functionName()
typedef SIGNATURE_OF_FUNC(funcType);
SIGNATURE_OF_FUNC(funcStub)
{
    std::cout << "This is just a stub, this shouldn't run" << std::endl;
    return 0;
}
static funcType *exampleFunc = funcStub;

// TODO: erase signatures
#define SIGNATURE_OF_CBK(name) int32_t name()
typedef SIGNATURE_OF_CBK(cbk);
SIGNATURE_OF_CBK(callbackFunction)
{
    std::cout << "I am the callback function" << std::endl;
    return 0;
}

#define SIGNATURE_OF_SET_CBK(functionName) int32_t functionName(cbk *)
typedef SIGNATURE_OF_SET_CBK(setCbkType);
SIGNATURE_OF_SET_CBK(setCbkStub)
{
    std::cout << "This is just a stub, this shouldn't run" << std::endl;
    return 0;
}
static setCbkType *setCbk = setCbkStub;

#define SIGNATURE_OF_RUN_ALL_CALLBACKS(functionName) int32_t functionName()
typedef SIGNATURE_OF_RUN_ALL_CALLBACKS(runAllCallbacksType);
SIGNATURE_OF_RUN_ALL_CALLBACKS(runAllCallbacksStub)
{
    std::cout << "This is just a stub, this shouldn't run" << std::endl;
    return 0;
}
static runAllCallbacksType *runAllCallbacks = runAllCallbacksStub;

HMODULE libModule = nullptr;
fs::file_time_type loadedDllWriteTime;

int32_t libraryUpkeep(fs::path& path) {
    {
        // return if library is up to date
        std::error_code errorCode;
        fs::file_time_type lastDllWriteTime = fs::last_write_time(path, errorCode);
        // NOTE: error value is os specific
        if (errorCode.value()) {
            // TODO: use custom logger or print to stderr
            std::cout << "ERROR " << errorCode.value() << ": " << errorCode.message() << std::endl;
            std::cout << path << std::endl;
            errorCode.clear();
            return -1;
        }
        bool dllHasChanged = lastDllWriteTime != loadedDllWriteTime;
        if (!dllHasChanged) {
            return 1;
        }
        loadedDllWriteTime = lastDllWriteTime;
    }

    // handle reload
    FreeLibrary(libModule);
    // TODO: error handle

    // TODO: delete the working copy i
    // TODO: create a working copy of the library
    // TODO: ensure a temp folder exists

    libModule = LoadLibraryA((LPCSTR)path.generic_string().c_str());
    if (!libModule)
    {
        std::cout << path << "Could not be loaded!" << std::endl;
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

    // DEBUG: run all callbacks in the dll
    runAllCallbacks = reinterpret_cast<runAllCallbacksType*>(GetProcAddress(libModule, "runAllCallbacks"));
    if (!runAllCallbacks)
    {
        std::cout << "Couldn't load the dll function "
            << "runAllCallbacks"
            << " with error code " << GetLastError() << std::endl;
        return 0;
    }
    runAllCallbacks();

    return 1;
}

int32_t libraryUpkeep(std::string& path) {
    fs::path fsPath = path;
    return libraryUpkeep(fsPath);
}
int main()
{
    // FIXME: current directories can ruin you. Ensure it's set properlly when using relative paths.
    //fs::current_path();
    std::string pathToLibrary = std::string("../SharedCode/bin/Debug/SharedCode.dll");
    std::cout << "Hello. I am the main app, the god of all the libraries" << std::endl;
    for (;;){
        std::cout << "Library Upkeep!" << std::endl;
        libraryUpkeep(pathToLibrary);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}