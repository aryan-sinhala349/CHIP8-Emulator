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
    using std::cerr;
    using std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    Emulator emu;
    emu.Update();

    SDL_Quit();

    system("pause");
    return 0;
}