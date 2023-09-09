#ifndef LOADER_PARAMS_HPP
#define LOADER_PARAMS_HPP

#include "libraries.hpp"

class LoaderParams {
public:
    LoaderParams(int x, int y, int width, int height, string identifier)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_identifier(identifier) {}
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    string getIdentifier() const { return m_identifier; }
    
    void update(int x, int y, int width, int height, string identifier);
    
private:
    int m_x, m_y;
    int m_width, m_height;
    string m_identifier;
};

#endif
