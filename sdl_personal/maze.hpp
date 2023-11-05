#ifndef MAZE_HPP
#define MAZE_HPP

#include "libraries.hpp"
#include "mazeBuilder.hpp"
#include "player.hpp"
#include "renderer.hpp"

const char MAZE_MAP_FILE_NAME[] = "maze.txt";
const int MAZE_ROOM_PADDING = 100;
const int roomWidth = 50;
const int roomHeight = 50;
const string roomTexIdentifier = "room";
const string playerTexIdentifier = "player";

class Maze {
public:
    static Maze * Instance();
    void update(Dirs dir);
    std::vector<MazeRoom*> * getMaze() { return m_pMazeBuilder->m_pRooms; }
    Player * getPlayer() { return m_pPlayer; }
    
private:
    Maze() {
        build();
        
        roomCount = m_pMazeBuilder->getRoomCount();
        calculateInitialPositions(m_pMazeBuilder->m_pRooms);
        m_pPlayer = new Player(getMaze()->at(0), roomTexIdentifier, playerTexIdentifier);
        running = true;
    }
    ~Maze() {}
    
    static Maze * m_pInstance;

    /**Builds the MazeRooms for first access**/
    bool build();
    
    bool recursiveCalc(int, int, MazeRoom*s);
    void calculateInitialPositions(std::vector<MazeRoom*>*);
    void moveMaze(int, int);
    std::vector<MazeRoom*> m_pRooms;
    
    int roomCount;
    MazeBuilder * m_pMazeBuilder;
    Player * m_pPlayer;
    
    bool sizeValuesProvided;
    bool running;
    
};

#endif
