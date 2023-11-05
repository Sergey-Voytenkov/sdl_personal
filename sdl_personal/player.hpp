#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "maze_room.hpp"
class Player {
public:
    Player(MazeRoom*, string, string);
    void move(Dirs);
    
private:
    string m_roomIdentifier;
    string m_playerIdentfier;
    MazeRoom* m_pRoom;
    
};

#endif
