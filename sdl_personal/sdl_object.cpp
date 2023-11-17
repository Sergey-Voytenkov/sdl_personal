#include "sdl_object.hpp"

SDLObject::SDLObject(const LoaderParams * pParams) :
    Object(pParams),
    m_position(pParams->getX(), pParams->getY()),
    m_velocity(0, 0), m_acceleration(0, 0) {
        m_width = pParams->getWidth();
        m_height = pParams->getHeight();
        m_identifier = pParams->getIdentifier();
        m_x = 0;
        m_y = 0;
}

void SDLObject::update() {
    m_velocity += m_acceleration;
    m_position += m_velocity;
}
void SDLObject::draw() {
    TextureManager::Instance()->draw(m_identifier,
                                      (int) m_position.getX(),
                                      (int) m_position.getY(),
                                      m_width, m_height,
                                      Renderer::Instance()->getRenderer(),
                                      SDL_FLIP_NONE);
}


void SDLObject::updateSize(int x, int y, int width, int height) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
};


