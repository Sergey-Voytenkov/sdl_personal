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

int* MazeRoom::getData() {
    return m_data;
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

void MazeRoom::updateAddToCords(float x, float y) {
    m_position.setX(m_position.getX() + x);
    m_position.setY(m_position.getY() + y);
}


std::pair<float, float> MazeRoom::getCords() {
    return std::make_pair<float, float>(m_position.getX(),
                                        m_position.getY());
}

void MazeRoom::setDimensions(int width, int height) {
    m_width = width;
    m_height = height;
}


void MazeRoom::updateIdentifier(string identfier) {
    m_identifier = identfier;
}

