#ifndef ASCII_ART_HPP
#define ASCII_ART_HPP

#import "libraries.hpp"
#include "texture_manager.hpp"
#include "renderer.hpp"


string font = "assets/CouriorPrime-Regular.ttf";

//SDL_Color White = { 255, 255, 255 };
//SDL_Color Black = { 0, 0, 0 };

class AsciiArt {
public:
    string characters = "@#BW8gMN6&9RQqE0d$DbpmOa5AH2GZeKPS3X4U%kwohFVyzIsCu{xfn}tJTi17c=jYL?l[]v<>+|)r(/\\*_!;^~\":,-'.`";

    AsciiArt() {}
    ~AsciiArt() {}
    static AsciiArt * Instance();
    
    bool load_font(SDL_Renderer * m_pRenderer, int size, SDL_Color color);
    bool calculate_map(string identifier, int x, int y);
    
    SDL_Texture * create_ascii_art();
    SDL_Surface * getFont() { return pFont; }
    
    int getCharacterWidth() { return (int) characters.length(); }
    
    map<pair<int, int>, Uint8> get_averageMap() { return m_averageMap; }
    
    
private:
    static AsciiArt * m_pInstance;
    
    int m_width  = NULL;
    int m_height = NULL;
    map<pair<int, int>, uint8_t> m_averageMap;
    SDL_Surface * pFont = nullptr;
    
    
    float clamp(uint8_t value, int start1, int end1, int start2, int end2){
        return (start2 + (end2 - start2) * ((value - start1) / (end1 - start1)));
    }
};
#endif
