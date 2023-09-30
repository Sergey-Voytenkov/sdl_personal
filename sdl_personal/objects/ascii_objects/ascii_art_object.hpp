#ifndef ASCII_ART_OBJECT_HPP
#define ASCII_ART_OBJECT_HPP

#include "libraries.hpp"
#include "sdl_object.hpp"
//#include "ascii_art.hpp"

class AsciiArtObject: public SDLObject {
public:
    AsciiArtObject(const LoaderParams * pParams) : SDLObject(pParams) {}
    ~AsciiArtObject() {}
    
    void draw();
    void update();
    
    void clean();
private:
    
};

#endif
