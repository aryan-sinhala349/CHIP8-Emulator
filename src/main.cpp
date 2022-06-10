#include "Emulator/Emulator.h"

int main(int argc, char** argv)
{
    auto emulator = new Emulator();
    emulator->Run();
    delete emulator;

    return 0;
}