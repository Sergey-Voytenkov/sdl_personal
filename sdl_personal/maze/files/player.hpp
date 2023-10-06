#ifndef player_HPP
#define player_HPP

#include <iostream>
#include "../../objects/maze_objects/maze_room.hpp"
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
