#ifndef MAZE_HPP
#define MAZE_HPP

#include "../other/libraries.hpp"
#include "files/mazeBuilder.hpp"
#include "files/player.hpp"
#include "../game/renderer/renderer.hpp"

char MAZE_MAP_FILE_NAME[] = "maze.txt";
const int MAZE_ROOM_PADDING = 100;
const int roomWidth = 50;
const int roomHeight = 50;


class Maze {
public:
    static Maze * Instance();
    Maze * update(int dir);
    std::vector<MazeRoom*> * getMaze() { return m_pMazeBuilder->&m_pRooms; }
    
private:
    Maze() {
        m_pMazeBuilder = new MazeBuilder(static_cast<char*>(MAZE_MAP_FILE_NAME));
        
        roomCount = m_pMazeBuilder->getRoomCount();
        m_pPlayer = new Player(getMaze());
        running = false;
    }
    ~Maze() {}
    
    static Maze * m_pInstance;

    /**Builds the MazeRooms for first access**/
    bool build(Room*);
    
    /**Builds the Rooms but does not calculate the positions**/
    void createPlainMazeRooms(Room*);
    bool recursiveCalc(int, int, Room*);
    /**Helper fucntions for initial creation**/
    MazeRoom * findMazeRoom(int);
    bool wasChecked(int);
    
    void calculateInitialPositions(Room*);
    std::map<int, MazeRoom*> * m_pMazeRooms;
    
    int roomCount;
    MazeBuilder * m_pMazeBuilder;
    Player * m_pPlayer;
    
    bool sizeValuesProvided;
    bool running;
    
};

#endif
