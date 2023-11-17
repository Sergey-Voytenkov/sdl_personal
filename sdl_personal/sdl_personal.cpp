#include <iostream>
#include "sdl_personal.hpp"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(void) {
    cout << "Starting..." << endl;
    
    game = Game::Instance();

    if (!game) {
        cout << "Failed to initialize Game." << endl;
        return -1;
    }

    cout << "Game initialized" << endl;


    if (!game->init(100, 100, 1200, 1000, "Window", false)) {
        delete game;
        return -1;
    }

    Uint32 frameStart, frameTime;

    while (game->running()) {
        frameStart = SDL_GetTicks();
        game->handle_input();
        game->update();
        game->render();
        
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
            SDL_Delay((int)(DELAY_TIME - frameTime));
    }

    cout << "Closing..." << endl;

    delete game;
    return 0;
}
