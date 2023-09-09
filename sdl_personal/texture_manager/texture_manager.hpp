#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "libraries.hpp"

class TextureManager {
public:
    static TextureManager * Instance() {
        if (!m_pInstance) m_pInstance = new TextureManager;
        return m_pInstance;
    }
    /**Set renderer to make commands simpler*/
    void setRenderer(SDL_Renderer * m_pRenderer) { m_pMainRenderer = m_pRenderer; };
    
    /**Get renderer*/
    SDL_Renderer * get_renderer() { return m_pMainRenderer; }

    /** Loads an image to memory. */
    bool load_image(string fileName, string identifier, SDL_Renderer * m_pRenderer);
    
    /**Simplified image_load *Must set Renderer with setRenderer()* */
    bool load_image(string fileName, string identifier);
    
    /**Loads an image to memory resized.*/
    bool load_image_resize(string fileName, string identifier, int resizeWidth, int resizeHeight, SDL_Renderer * m_pRenderer);
    
    /**Simplified image_load_resized *Must set Renderer with setRenderer()* */
    bool load_image_resize(string fileName, string identifier, int resizedWidth, int resizeHeight);
    
    /**Loads texture from surface *OVERLOADS TEXTURE**/
    bool load_texture_from_surface(string identifier, SDL_Renderer * m_pRenderer);
    
    /**Loads texture from surface *OVERLOADS TEXTURE*,  make sure that renderer is set*/
    bool load_texture_from_surface(string identifier);
    
    /**Get preloaded texture from TextureMap**/
    SDL_Texture * get_texture(string identifier);
    
    /**Get preloaded surface from SurfaceMap**/
    SDL_Surface * get_surface(string identifier);
    ;
    
    void draw(string id, int x, int y, int height, int width, SDL_Renderer *pRenderer, SDL_RendererFlip flip);
    
    void drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip);

    

    /**Destroys texture manager**/
    static void destroy() {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
    
private:
    TextureManager() {}
    ~TextureManager() { clear(); }
    
    static TextureManager * m_pInstance;
    SDL_Renderer * m_pMainRenderer = nullptr;
    void clear();
    
    map<string, SDL_Texture*> m_textureMap;
    map<string, SDL_Surface*> m_surfaceMap;
};
#endif
