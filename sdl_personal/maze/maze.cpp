#include "maze.hpp"

Maze * Maze::m_pInstance = nullptr;

Maze * Maze::Instance() {
    if (!m_pInstance) m_pInstance = new Maze;
    return m_pInstance;
}

bool Maze::build() {
    m_pMazeBuilder = new MazeBuilder(static_cast<char*>(MAZE_MAP_FILE_NAME), roomWidth, roomHeight, roomTexIdentifier);
    
    roomCount = m_pMazeBuilder->getRoomCount();
    
    calculateInitialPositions(m_pMazeBuilder->m_pRooms);
    
    return true;
}


void Maze::calculateInitialPositions(std::vector<MazeRoom*>* pRooms) {
    //Calculate center of the view to pass on
    std::pair<int, int> screenSize = Renderer::Instance()->getScreenSizeReference();
    int x = (screenSize.first/2) - (roomWidth/2);
    int y = (screenSize.second/2) - (roomHeight/2);
    
    recursiveCalc(x, y, pRooms->at(0));
}

bool Maze::recursiveCalc(int curX, int curY, MazeRoom* pRoom) {
    pRoom->updateCords(curX, curY);
    
    if (!pRoom->getRoom(Dirs::north)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX, curY+MAZE_ROOM_PADDING, pRoom->getRoom(Dirs::north));
    }
    
    if (!pRoom->getRoom(Dirs::south)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX, curY-MAZE_ROOM_PADDING, pRoom->getRoom(Dirs::south));
    }
    
    if (!pRoom->getRoom(Dirs::east)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX+MAZE_ROOM_PADDING, curY, pRoom->getRoom(Dirs::east));
    }
    
    if (!pRoom->getRoom(Dirs::west)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX-MAZE_ROOM_PADDING, curY, pRoom->getRoom(Dirs::west));
    }
    
    return true;
}
