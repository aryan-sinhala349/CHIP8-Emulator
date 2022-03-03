#include "Emulator/Emulator.h"

Emulator::Emulator()
{
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

void Emulator::Update()
{
    const float c_TimeBetweenSteps = 1 / 700.0f;
    const float c_TimeBetweenFrames = 1 / 60.0f;
    const uint32_t c_Scale = 5;

    m_Window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64 * c_Scale, 32 * c_Scale, SDL_WINDOW_SHOWN);

    float firstTime = SDL_GetTicks() / 1000.0f;
    float lastTime = SDL_GetTicks() / 1000.0f;
    float passedTime = 0.0f;
    
    float unprocessedTime = 0.0f;
    float unprocessedRenderTime = 0.0f;

    bool running = true;

    SDL_Event event;

    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    running = false;
                    break;
                }
            }
        }

        if (!running)
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

    SDL_DestroyWindow(m_Window);
}

void Emulator::Step()
{

}

void Emulator::Render()
{

}