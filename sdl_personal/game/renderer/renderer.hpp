#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Renderer {
public:
    static Renderer * Instance();
    
    bool init(int posX, int posY, int width, int height, string windowName);
    
    SDL_Renderer * getRenderer() { return m_pRenderer; }
    SDL_Window * getWindow() { return m_pWindow; }
    
private:
    Renderer() {
        m_pRenderer = nullptr;
        m_pWindow = nullptr;
    }
    ~Renderer() {}
    
    static Renderer * s_pInstance;
    SDL_Renderer * m_pRenderer;
    SDL_Window * m_pWindow;
};

#endif
