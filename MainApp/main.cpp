#include <iostream>
#include <windows.h>
#define FUNC_SIGNATURE(funcName) int funcName()
typedef FUNC_SIGNATURE(funcType);
FUNC_SIGNATURE(funcStub){
    return 0;
}
// TODO: make static
funcType *func = funcStub;
int main()
{
    std::cout << "Hello. I am the main app, the god of all the libraries" << std::endl;
    HMODULE loadedLib = LoadLibraryA("../../../SharedCode/bin/Debug/SharedCode.dll");
    if (!loadedLib)
    {
        std::cout << "Couldn't load the library with error code " << GetLastError() << std::endl;
    }
    else
    {
        // TODO: get function
        func = reinterpret_cast<funcType*>(GetProcAddress(loadedLib, "exampleFunc"));
        func();
    }
}