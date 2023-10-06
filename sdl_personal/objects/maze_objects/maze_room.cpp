#include "maze_room.hpp"
void MazeRoom::update() {
    SDLObject::update();
}

void MazeRoom::draw() {
    SDLObject::draw();
}

void MazeRoom::clean() {
    
}

void MazeRoom::setId(int id) {
    m_id = id;
}

int MazeRoom::getId() {
    return m_id;
}

void MazeRoom::setRoom(Dirs dir, MazeRoom* room) {
    switch (dir) {
        case Dirs::north:
            m_pNorth = room;
            break;
        case Dirs::south:
            m_pSouth = room;
            break;
        case Dirs::east:
            m_pEast = room;
            break;
        case Dirs::west:
            m_pEast = room;
            break;
            
        default:
            break;
    }
    return;
}

MazeRoom* MazeRoom::getRoom(Dirs dir) {
    switch (dir) {
        case Dirs::north:
            return m_pNorth;
            break;
        case Dirs::south:
            return m_pSouth;
            break;
        case Dirs::east:
            return m_pEast;
            break;
        case Dirs::west:
            return m_pWest;
            break;
            
        default:
            break;
    }
    
    return nullptr;
}

std::pair<int, int> MazeRoom::getRoomCords() {
    return std::pair<int, int>(m_roomX, m_roomY);
}

void MazeRoom::setRoomCords(int x, int y) {
    m_roomX = x;
    m_roomY = y;
}

void MazeRoom::updateCords(float x, float y) {
    m_position.setX(x);
    m_position.setY(y);
}

std::pair<float, float> MazeRoom::getCords() {
    return std::make_pair<float, float>(m_position.getX(),
                                        m_position.getY());
}

void MazeRoom::updateIdentifier(string identfier) {
    m_identifier = identfier;
}
