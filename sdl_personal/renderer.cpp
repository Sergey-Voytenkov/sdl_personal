#include "renderer.hpp"

Renderer * Renderer::s_pInstance = nullptr;

Renderer * Renderer::Instance() {
    if (!s_pInstance) s_pInstance = new Renderer;
    return s_pInstance;
}

bool Renderer::init(int posX, int posY, int width, int height, const char * identifier, bool fullscreen) {
    
    uint32_t flag = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;
    m_pWindow = SDL_CreateWindow(identifier, posX, posY, width, height, flag);
    SDL_CreateWindow(identifier, posX, posY, width, height, flag);
    if (!m_pWindow) {
        cout << "Failed to initialize SDL_Window. " << SDL_GetError() << endl;
        return false;
    }
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);


    // m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    // if (!m_pRenderer) {
    //     cout << "Failed to create a Accelerated Renderer. " << SDL_GetError() << endl;
    //     cout << "Attempting Software Renderer... ";
        
    //     m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
    //     if (m_pRenderer)
    //         cout << "Succeded.";
    //     else {
    //         cout << "Unable to create Renderer. " << SDL_GetError() << endl;
    //         return false;
    //     }
    // }
    
    return true;
}
