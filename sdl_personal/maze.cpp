#include "maze.hpp"

Maze * Maze::m_pInstance = nullptr;

Maze * Maze::Instance() {
    if (!m_pInstance) m_pInstance = new Maze;
    return m_pInstance;
}


bool Maze::build() {
    m_pMazeBuilder = new MazeBuilder(MAZE_MAP_FILE_NAME, roomWidth, roomHeight, roomTexIdentifier);

    if (!m_pMazeBuilder->buildRooms()) return false;

    roomCount = m_pMazeBuilder->getRoomCount();
    
    calculateInitialPositions(m_pMazeBuilder->m_pRooms);

    m_pPlayer = new Player(m_pMazeBuilder->m_pRooms->at(0), roomTexIdentifier, playerTexIdentifier);
    
    m_running = true;
    return true;
}

void Maze::update(Dirs dir) {
    switch (dir) {
        case Dirs::north:
            moveMaze(0, MAZE_ROOM_PADDING);
            break;
        case Dirs::south:
            moveMaze(0, -MAZE_ROOM_PADDING);
            break;
        case Dirs::east:
            moveMaze(MAZE_ROOM_PADDING, 0);
            break;
        case Dirs::west:
            moveMaze(-MAZE_ROOM_PADDING, 0);
            break;
        
        default:
            break;
    }
}

void Maze::moveMaze(int moveX, int moveY) {
    //Uses directly the m_pRooms from MazeBuilder because 
    // function is located in the type. 

    for (int i = 0; i < m_pRooms.size() || i < roomCount; i++) {
        //m_pRooms[i]->updateAddToCords(moveX, moveY);
        //m_pMazeBuilder->m_pRooms->at(i)->updateAddToCords(moveX, moveY);
        ((MazeRoom*)(m_pRooms[i]))->updateAddToCords(moveX, moveY);
        
    }
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
    
    if (pRoom->getRoom(Dirs::north) != nullptr && !pRoom->getRoom(Dirs::north)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX, curY-MAZE_ROOM_PADDING, pRoom->getRoom(Dirs::north));
    }
    
    if (pRoom->getRoom(Dirs::south) != nullptr && !pRoom->getRoom(Dirs::south)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX, curY+MAZE_ROOM_PADDING, pRoom->getRoom(Dirs::south));
    }
    
    if (pRoom->getRoom(Dirs::east) != nullptr && !pRoom->getRoom(Dirs::east)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX+MAZE_ROOM_PADDING, curY, pRoom->getRoom(Dirs::east));
    }
    
    if (pRoom->getRoom(Dirs::west) != nullptr && !pRoom->getRoom(Dirs::west)->initialPositionCalculated) {
        pRoom->initialPositionCalculated = true;
        recursiveCalc(curX-MAZE_ROOM_PADDING, curY, pRoom->getRoom(Dirs::west));
    }
    
    return true;
}
