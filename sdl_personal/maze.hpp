#ifndef MAZE_HPP
#define MAZE_HPP

#include "libraries.hpp"
#include "mazeBuilder.hpp"
#include "player.hpp"
#include "renderer.hpp"

const char MAZE_MAP_FILE_NAME[] = "C:\\Users\\Desktop\\Projects\\CPP\\sdl_personal\\x64\\Debug\\maze.txt";
const int MAZE_ROOM_PADDING = 200;
const int roomWidth = 100;
const int roomHeight = 100;
const string roomTexIdentifier = "room";
const string playerTexIdentifier = "player";

class Maze {
public:
    static Maze * Instance();
    void update(Dirs dir);
    /**Builds the MazeRooms for first access**/
    bool build();
    std::vector<MazeRoom*> * getMaze() { return m_pMazeBuilder->m_pRooms; }
    Player * getPlayer() { return m_pPlayer; }
    bool running() { return m_running; }

private:
    Maze() { 
        m_running = false; 
        m_pRooms = {}; // does this work (?) lets see if its crashes lol
        m_pMazeBuilder = nullptr;
        m_pPlayer = nullptr;
        sizeValuesProvided = false;
        m_running = false;
        roomCount = 0;
    }
    ~Maze() {}
    
    static Maze * m_pInstance;

    
    
    bool recursiveCalc(int, int, MazeRoom*s);
    void calculateInitialPositions(std::vector<MazeRoom*>*);
    void moveMaze(int, int);
    std::vector<SDLObject*> m_pRooms;
    
    int roomCount;
    MazeBuilder * m_pMazeBuilder;
    Player * m_pPlayer;
    
    bool sizeValuesProvided;
    bool m_running;
    
};

#endif
