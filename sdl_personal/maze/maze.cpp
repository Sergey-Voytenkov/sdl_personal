#include "maze.hpp"

Maze * Maze::m_pInstance = nullptr;

Maze * Maze::Instance() {
    if (!m_pInstance) m_pInstance = new Maze;
    return m_pInstance;
}

bool Maze::build(Room* rooms) {
    if (rooms == nullptr) return false;
    
    // Create rooms with default values
    createPlainMazeRooms(rooms);
    
    // Calculates their initial positions around first room
    calculateInitialPositions(&rooms[0]);
    
    
    return true;
}

void Maze::createPlainMazeRooms(Room * rooms) {
    Room* pRoom;
    MazeRoom* pMazeRoom;
    
    for (int i = 0; i < roomCount; i++) {
        pRoom = &rooms[i];
        pMazeRoom = new MazeRoom(new LoaderParams(0, 0, roomWidth, roomHeight, "room"), pRoom->x, pRoom->y, pRoom->id);
        pMazeRoom->initialPositionCalculated = false;
        
        m_pMazeRooms->insert(std::pair<int, MazeRoom*>(pRoom->id, pMazeRoom));
    }
}

void Maze::calculateInitialPositions(Room* room) {
    //Calculate center of the view to pass on
    std::pair<int, int> screenSize = Renderer::Instance()->getScreenSizeReference();
    int x = screenSize.first - (1/roomWidth);
    int y = screenSize.second - (1/roomHeight);
    
    recursiveCalc(x, y, room);
}

bool Maze::recursiveCalc(int curX, int curY, Room* room) {
    findMazeRoom(room->id)->updateCords(curX, curY);
    
    if (!wasChecked(room->north->id)) {
        findMazeRoom(room->id)->initialPositionCalculated = true;
        recursiveCalc(curX, curY+MAZE_ROOM_PADDING, room->north);
    }
    if (!wasChecked(room->south->id)) {
        findMazeRoom(room->id)->initialPositionCalculated = true;
        recursiveCalc(curX, curY+MAZE_ROOM_PADDING, room->south);
    }
    if (!wasChecked(room->east->id)) {
        findMazeRoom(room->id)->initialPositionCalculated = true;
        recursiveCalc(curX-MAZE_ROOM_PADDING, curY, room->east);
    }
    if (!wasChecked(room->west->id)) {
        findMazeRoom(room->id)->initialPositionCalculated = true;
        recursiveCalc(curX+MAZE_ROOM_PADDING, curY, room->west);
    }
    
    return true;
}

MazeRoom * Maze::findMazeRoom(int roomId) {
    if (m_pMazeRooms->find(roomId) == m_pMazeRooms->end())
        return NULL;
    return m_pMazeRooms->find(roomId)->second;
}

bool Maze::wasChecked(int roomId) {
    if (findMazeRoom(roomId) == NULL)
        return true;
    return findMazeRoom(roomId)->initialPositionCalculated;
}
