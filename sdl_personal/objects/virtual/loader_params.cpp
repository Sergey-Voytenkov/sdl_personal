#include "loader_params.hpp"

void LoaderParams::update(int x, int y, int width, int height, string identifier) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_identifier = identifier;
}

