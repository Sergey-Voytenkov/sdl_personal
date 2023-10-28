#ifndef SDL_OBJECT_HPP
#define SDL_OBJECT_HPP

#include "../../other/libraries.hpp"
#include "loader_params.hpp"
#include "object.hpp"
#include "../../game/renderer/renderer.hpp"
#include "../../texture_manager/texture_manager.hpp"


class SDLObject: public Object {
public:
    SDLObject(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    
protected:
    void updateSize(int x, int y, int width, int height);
    
    string m_identifier;
    Vector2 m_position;
    Vector2 m_velocity;
    Vector2 m_acceleration;

    int m_x, m_y;
    int m_width, m_height;
};

#endif
