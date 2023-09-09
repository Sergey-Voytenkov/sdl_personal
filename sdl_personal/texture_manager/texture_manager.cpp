#include "texture_manager.hpp"

TextureManager * TextureManager::m_pInstance = nullptr;

bool TextureManager::load_image(string fileName, string identifier, SDL_Renderer * m_pRenderer) {
    if (m_textureMap[identifier] || m_surfaceMap[identifier]) {
        cout << "Identifier " << identifier << " already exists, not loading new instance." << endl;
        return false;
    }
    if (!m_pRenderer) m_pRenderer = m_pMainRenderer;
    
    SDL_Surface * pSurface = IMG_Load(fileName.c_str());
    if (!pSurface) {
        cout << "Failed to load IMG " << fileName << ". " << SDL_GetError() << endl;
        SDL_FreeSurface(pSurface);
        return false;
    }
    
    SDL_Texture * pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
    if (!pTexture) {
        cout << "Unable to create texture from surface on IMG " << fileName << ". " << SDL_GetError();
        SDL_FreeSurface(pSurface);
        SDL_DestroyTexture(pTexture);
        return false;
    }
    
    m_surfaceMap[identifier] = pSurface;
    m_textureMap[identifier] = pTexture;
    
    return true;
}

bool TextureManager::load_image(string fileName, string identifier) {
    return load_image(fileName, identifier, m_pMainRenderer);
}

bool TextureManager::load_image_resize(string fileName, string identifier, int resizeWidth, int resizeHeight, SDL_Renderer *m_pRenderer) {
    if (m_textureMap[identifier] || m_surfaceMap[identifier]) {
        cout << "Identifier " << identifier << " already exists, not loading new instance." << endl;
        return false;
    }
    
    if (!m_pRenderer) m_pRenderer = m_pMainRenderer;
    
    SDL_Surface * pSurface = IMG_Load(fileName.c_str());
    if (!pSurface) {
        cout << "Failed to load IMG " << identifier << ". " << SDL_GetError() << endl;
        SDL_FreeSurface(pSurface);
        return false;
    }
    
    SDL_Rect * tempRect = new SDL_Rect();
    tempRect->x = tempRect->x = 0;
    tempRect->w = resizeWidth;
    tempRect->h = resizeHeight;
    
    SDL_BlitScaled(pSurface, NULL, pSurface, tempRect);
    if (!pSurface) {
        cout << "Failed to scale image " << identifier << ". " << SDL_GetError();
        delete tempRect;
        SDL_FreeSurface(pSurface);
        return false;
    }
    
    delete tempRect;
    
    SDL_Texture * pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
    if(!pTexture) {
        cout << "Unable to create texture from surface on IMG " << fileName << ". " << SDL_GetError();
        SDL_FreeSurface(pSurface);
        SDL_DestroyTexture(pTexture);
        return false;
    }
    m_textureMap[identifier] = pTexture;
    m_textureMap[identifier] = pTexture;
    
    return true;
}

bool TextureManager::load_image_resize(string fileName, string identifier, int resizedWidth, int resizeHeight) {
    return load_image_resize(fileName, identifier, resizedWidth, resizeHeight, m_pMainRenderer);
}

bool TextureManager::load_texture_from_surface(string identifier, SDL_Renderer * m_pRenderer) {
    if (!m_surfaceMap[identifier]) {
        cout << "No identifier for " << identifier << "exits." << endl;
        return false;
    }
    
    if (!m_pRenderer) m_pRenderer = m_pMainRenderer;
    
    SDL_Surface * pSurface = m_surfaceMap[identifier];
    if (!pSurface) {
        cout << "Failed to load surface " << identifier << ". " << endl;
        return false;
    }
    
    SDL_Texture * pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
    if (!pTexture) {
        cout << "Failed to create a texture for " << identifier << ". " << SDL_GetError() << endl;
        return false;
    }
    
    SDL_DestroyTexture(m_textureMap[identifier]);
    m_textureMap[identifier] = pTexture;
    
    return true;
}

bool TextureManager::load_texture_from_surface(string identifier) {
    return load_texture_from_surface(identifier, m_pMainRenderer);
}


SDL_Texture * TextureManager::get_texture(string identifier) {
    return m_textureMap[identifier];
}

SDL_Surface * TextureManager::get_surface(string identifier) {
    return m_surfaceMap[identifier];
}

void TextureManager::draw(string id, int x, int y, int height, int width, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = srcRect.w = width;
    dstRect.h = srcRect.h = height;
    
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = srcRect.w = width;
    dstRect.h = srcRect.h = height;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, 0, flip);

};

void TextureManager::clear() {
    map<string, SDL_Texture*>::iterator iterator = m_textureMap.begin();
    while (iterator != m_textureMap.end()) {
        SDL_DestroyTexture(iterator->second);
        m_textureMap.erase(iterator);
        iterator = m_textureMap.begin();
    }
    delete &m_textureMap;
    
    map<string, SDL_Surface*>::iterator iterator2 = m_surfaceMap.begin();
    while (iterator2 != m_surfaceMap.end()) {
        SDL_FreeSurface(iterator2->second);
        m_surfaceMap.erase(iterator2);
        iterator2 = m_surfaceMap.begin();
    }
    delete &m_surfaceMap;
}


