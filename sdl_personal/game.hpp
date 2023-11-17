#ifndef GAME_HPP
#define GAME_HPP

#include "texture_manager.hpp"
#include "libraries.hpp"

#include "renderer.hpp"
#include "object.hpp"
#include "maze.hpp"
//#include "ascii_art_object.hpp"


class Game {
public:
    Game() {
        m_pMaze = nullptr;
        m_pPlayer = nullptr;
        m_pWindow = nullptr;
        m_pRenderer = nullptr;
        m_pInstance = nullptr;
        g_bRunning = false;
    }
    ~Game() { 
        clean();
     }
    
    static Game * Instance();

    bool init(int posX, int posY, int width, int height, const char * identifier, bool fullscreen);
    
    bool update();
    bool handle_input();
    bool render();
    
    bool running() { return g_bRunning; }

    void stopRunning() { g_bRunning = false; }
    SDL_Window * getWindow() { return m_pWindow; }
    SDL_Renderer * getRenderer() { return m_pRenderer; }
    
private:
    static Game * m_pInstance;
    
    bool g_bRunning;
    SDL_Window * m_pWindow;
    SDL_Renderer * m_pRenderer;
   
    Player * m_pPlayer;
    Maze * m_pMaze;
    
    vector<Object*> m_Objects;
    void clean();
 
};


#endif
