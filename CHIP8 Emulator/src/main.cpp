#include <SDL.h>
#include <cstdlib>
#include <iostream>

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

    SDL_Window* win = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 32, SDL_WINDOW_SHOWN);
    
    if (!win)
    {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Delay(1000);

    SDL_DestroyWindow(win);
    SDL_Quit();

    system("pause");
    return 0;
}