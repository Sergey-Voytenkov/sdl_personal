#include <iostream>
#include "main.hpp"

int main(int argc, const char * argv[]) {
    cout << "Starting..." << endl;
    
    game = Game::Instance();
    
    if (!game) {
        cout << "Failed to initialize Game." << endl;
        return 1;
    }
    
    if (!game->init(100, 100, 1200, 1000, "Window", false)) {
        delete game;
        return 1;
    }
        
    while (game->running()) {
        game->handle_input();
        game->update();
        game->render();
    }
      
    cout << "Closing..." << endl;
    
    delete game;
    return 0;
}
