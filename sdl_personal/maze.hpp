#ifndef MAZE_HPP
#define MAZE_HPP

#include "libraries.hpp"
#include "mazeBuilder.hpp"
#include "player.hpp"
#include "renderer.hpp"

const char MAZE_MAP_FILE_NAME[] = "C:\\Users\\Desktop\\Projects\\sdl_personal\\x64\\Debug\\maze.txt";
const int MAZE_ROOM_PADDING = 100;
const int roomWidth = 50;
const int roomHeight = 50;
const string roomTexIdentifier = "C:\\Users\\Desktop\\Projects\\sdl_personal\\x64\\Debug\\room.png";
const string playerTexIdentifier = "C:\\Users\\Desktop\\Projects\\sdl_personal\\x64\\Debug\\player.png";

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
    }
    ~Maze() {}
    
    static Maze * m_pInstance;

    
    
    bool recursiveCalc(int, int, MazeRoom*s);
    void calculateInitialPositions(std::vector<MazeRoom*>*);
    void moveMaze(int, int);
    std::vector<MazeRoom*> m_pRooms;
    
    int roomCount;
    MazeBuilder * m_pMazeBuilder;
    Player * m_pPlayer;
    
    bool sizeValuesProvided;
    bool m_running;
    
};

#endif
