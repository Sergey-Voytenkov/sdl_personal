#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

class Renderer {
public:
    static Renderer * Instance();
    
    bool init(int posX, int posY, int width, int height, const char * identifier, bool fullscreen);
    
    SDL_Renderer * getRenderer() { return m_pRenderer; }
    SDL_Window * getWindow() { return m_pWindow; }
    void setScreenSizeReference(int width, int height) { m_width = width; m_height = height; }
    std::pair<int, int> getScreenSizeReference() { return std::pair<int, int>(m_width, m_height); }
private:
    Renderer() {
        m_pRenderer = nullptr;
        m_pWindow = nullptr;
        m_width = NULL;
        m_height = NULL;
    }
    ~Renderer() {}
    
    static Renderer * s_pInstance;
    SDL_Renderer * m_pRenderer;
    SDL_Window * m_pWindow;
    
    int m_width;
    int m_height;
};

#endif
