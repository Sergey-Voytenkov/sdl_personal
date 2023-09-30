#include "room_instance.hpp"

void MazeRoom::updateCords(float x, float y) {
    m_position.setX(x);
    m_position.setY(y);
}

void MazeRoom::update() {
    SDLObject::update();
}

void MazeRoom::draw() {
    SDLObject::draw();
}

void MazeRoom::clean() {
    
}
