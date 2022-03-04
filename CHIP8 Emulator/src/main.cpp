#include <iostream>
#include <SDL.h>

#include "Emulator/Emulator.h"

#if defined(__WIN32__)
int wmain(int argc, char** argv)
{
    main(argc, argv);
}
#endif

int main(int argc, char** argv)
{
    Emulator* emulator = new Emulator();
    emulator->Update();
    delete emulator;

    system("pause");
    return 0;
}