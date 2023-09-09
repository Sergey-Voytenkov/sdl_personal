#include "ascii_art.hpp"

AsciiArt * AsciiArt::m_pInstance = nullptr;

AsciiArt * AsciiArt::Instance() {
    if (!m_pInstance) m_pInstance = new AsciiArt;
    return m_pInstance;
}

bool AsciiArt::load_font(SDL_Renderer * m_pRenderer, int size, SDL_Color color) {
    SDL_FreeSurface(pFont);
    
    TTF_Font * pTempFont = TTF_OpenFont(font.c_str(), size);
    if (!pTempFont) return false;
     
    SDL_Surface * pSurface = TTF_RenderText_Solid(pTempFont, characters.c_str(), color);
    if (!pSurface) return false;
   
    pFont = pSurface;
    return true;
}

bool AsciiArt::calculate_map(string identifier, int x, int y) {
    if (!TextureManager::Instance())
        return false;
    
    SDL_Surface * image = TextureManager::Instance()->get_surface(identifier);
    if (!image) return false;
    
    m_width = image->w;
    m_height = image->h;
    
    if (SDL_MUSTLOCK(image))
        SDL_LockSurface(image);
    
    Uint32 * pixels = (Uint32*) image->pixels;
    int pixel = NULL;
    int bpp = image->format->BytesPerPixel;
    float sum = 0;
    int counter = 0;
    
    
    for (int curY = 0; curY < image->h; curY+=y) {
        for (int curX = 0; curX < image->w; curX+=x) {
            for (int pY = 0; pY < y; pY++)
                for (int pX = 0; pX < x; pX++) {
                    if (curX + pX > image->w) continue;
                    if (curY + pY > image->h) continue;
                    
                    pixel = (pY * image->w + image->w * curY) + (pX*bpp + curX*bpp);
                    sum += (pixels[pixel] + pixels[pixel+1] + pixels[pixel+2]) / 3;
                    counter++;
                }
            
            m_averageMap[make_pair(curX, curY)] = (uint8_t) (sum / counter);
            sum = counter = 0;
        }
    }
    
    SDL_UnlockSurface(image);
    return true;
}

SDL_Texture * AsciiArt::create_ascii_art() {
    if (!pFont) {
        cout << "Font has not been loaded, cant create ascii art." << endl;
        return NULL;
    }
    
    SDL_Surface * pSurface = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0, 0, 0, 0);
    
    if (SDL_MUSTLOCK(pFont))
        SDL_LockSurface(pSurface);
    
    int charSize = (int) characters.size();
    int fontX = pFont->w / charSize;
    int fontY = pFont->h;
    int index = 0;
    
    int y = 0;
    int x = 0;
    uint8_t color = 0x00;
    float mapedColor = 0;


//    uint8_t max = 0xff; // 255 or 0b1111111
//    uint8_t min = 0x00; // 0 or 0b00000000

    
    int bbp = pSurface->format->BytesPerPixel;
    int fbbp = pFont->format->BytesPerPixel;
    
    for (::map<pair<int, int>, Uint8>::iterator iterator = m_averageMap.begin(); iterator != m_averageMap.end(); iterator++) {
        x = iterator->first.first;
        y = iterator->first.second;
        color = iterator->second;
        
        mapedColor = clamp(color, 0x00, 0xff, 0, charSize);
        index = (int) mapedColor;
        
        for (int i = 0; i < fontY; i++) {
            if (i > pSurface->h) continue;
            
            for (int j = x; j < fontX; j++) {
                if (j > pSurface->w) continue;
                
                pSurface[(y * pSurface->w + fontY * pSurface->w) + (x*bbp + j*bbp)] = pFont[(i * pFont->w) + (index*fbbp + j*fbbp)];
                pSurface[(y * pSurface->w + fontY * pSurface->w) + (x*bbp + j*bbp + 1)] = pFont[(i * pFont->w) + (index*fbbp + j*fbbp + 1)];
                pSurface[(y * pSurface->w + fontY * pSurface->w) + (x*bbp + j*bbp + 2)] = pFont[(i * pFont->w) + (index*fbbp + j*fbbp + 2)];
            }
        }
    }
    
    SDL_UnlockSurface(pSurface);
    
    SDL_Texture * pTexture = SDL_CreateTextureFromSurface(TextureManager::Instance()->get_renderer(), pSurface);
    if (!pTexture) {
        cout << "Failed to create ascii art texture. " << SDL_GetError() << endl;
        
        SDL_FreeSurface(pSurface);
        SDL_DestroyTexture(pTexture);
        return NULL;
    }
    
    
    return pTexture;
}
