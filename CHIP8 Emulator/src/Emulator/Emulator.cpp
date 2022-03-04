#include "Emulator/Emulator.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

static uint32_t g_OnColor = 0xffffffff;
static uint32_t g_OffColor = 0x000000ff;
static uint32_t g_WindowCount = 0;

Emulator::Emulator()
{
    //Initialize SDL
    if (!g_WindowCount++)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING))
        {
            cerr << "SDL_Init Failure: " << SDL_GetError() << endl;
            m_Running = false;
            return;
        }
    }

    //Setup the font
    const uint16_t c_FontStartPointInMemory = 0x50;
    const uint8_t c_FontLUTLength = 0x50;
    const uint8_t c_FontLUT[c_FontLUTLength] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (uint16_t i = 0; i < c_FontLUTLength; i++)
        m_RAM[i + c_FontStartPointInMemory] = c_FontLUT[i];
}

Emulator::~Emulator()
{
    if (m_Renderer)
        SDL_DestroyRenderer(m_Renderer);

    if (m_Window)
        SDL_DestroyWindow(m_Window);

    if (!--g_WindowCount)
        SDL_Quit();
}

void Emulator::Update()
{
    const float c_TimeBetweenSteps = 1 / 700.0f;
    const float c_TimeBetweenFrames = 1 / 60.0f;
    const uint32_t c_Scale = 10;

    //Create the window
    m_Window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64 * c_Scale, 32 * c_Scale, SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        cerr << "SDL_CreateWindow Failure: " << SDL_GetError() << endl;
        m_Running = false;
        return;
    }
    
    //Create the renderer
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_Renderer)
    {
        cerr << "SDL_CreateRenderer Failure: " << SDL_GetError() << endl;
        m_Running = false;
        return;
    }

    float firstTime = SDL_GetTicks() / 1000.0f;
    float lastTime = SDL_GetTicks() / 1000.0f;
    float passedTime = 0.0f;
    
    float unprocessedTime = 0.0f;
    float unprocessedRenderTime = 0.0f;

    SDL_Event event;

    while (m_Running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    m_Running = false;
                    break;
                }
            }
        }

        if (!m_Running)
            continue;

        firstTime = SDL_GetTicks() / 1000.0f;
        passedTime = firstTime - lastTime;
        lastTime = firstTime;

        unprocessedTime += passedTime;
        unprocessedRenderTime += passedTime;

        while (unprocessedTime >= c_TimeBetweenSteps)
        {
            unprocessedTime -= c_TimeBetweenSteps;
            Step();

            while (unprocessedRenderTime >= c_TimeBetweenFrames)
            {
                unprocessedRenderTime -= c_TimeBetweenFrames;
                Render();
            }
        }
    }
}

void Emulator::Step()
{

}

void Emulator::Render()
{
    for (uint16_t x = 0; x < 64; x++)
    {
        for (uint16_t y = 0; y < 32; y++)
        {
            m_Display[x + 64 * y] = (x / 3 + y) % 3 == 0;
        }
    }

    uint32_t display[0x800] = { 0 };

    for (uint16_t x = 0; x < 64; x++)
    {
        for (uint16_t y = 0; y < 32; y++)
        {
            bool state = m_Display[x + 64 * y];
            uint32_t color = state * g_OnColor + !state * g_OffColor;
            display[x + 64 * y] = color;
        }
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(display, 64, 32, 32, 64 * 4, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    SDL_LockSurface(surface);
    surface->pixels = display;
    SDL_UnlockSurface(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_RenderClear(m_Renderer);

    if (texture)
        SDL_RenderCopy(m_Renderer, texture, nullptr, nullptr);

    SDL_RenderPresent(m_Renderer);

    SDL_FreeSurface(surface);

    if (texture)
        SDL_DestroyTexture(texture);    
}