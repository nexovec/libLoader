#include <iostream>
#include <windows.h>
#include <stdint.h>
#define FUNC_SIGNATURE(funcName) int funcName()
typedef FUNC_SIGNATURE(funcType);
FUNC_SIGNATURE(funcStub)
{
    return 0;
}
static funcType *func = funcStub;
int main()
{
    // load the dll
    std::cout << "Hello. I am the main app, the god of all the libraries" << std::endl;
    HMODULE loadedLib = LoadLibraryA("../../../SharedCode/bin/Debug/SharedCode.dll");
    if (!loadedLib)
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
        return -1;
    }

    // load and call a function from the dll
    func = reinterpret_cast<funcType *>(GetProcAddress(loadedLib, "exampleFunc"));
    if (!func)
    {
        std::cout << "Couldn't load the dll function with error code " << GetLastError() << std::endl;
    }
    func();

    // TODO: give a callback function to the dll
}