#include <iostream>
#include <SDL.h>

#include "Emulator/Memory.h"

#if defined(__WIN32__)
int wmain(int argc, char** argv)
{
    main(argc, argv);
}
#endif

int main(int argc, char** argv)
{
    using std::cout;
    using std::endl;

    Memory mem;
    cout << (int)mem.ReadMemory(0x000) << endl;

    mem.WriteMemory(0x000, 0xFF);
    cout << (int)mem.ReadMemory(0x000) << endl;

    mem.WriteMemory(0x1000, 0x10);
    cout << (int)mem.ReadMemory(0x1000) << endl;

    system("pause");
    return 0;
}