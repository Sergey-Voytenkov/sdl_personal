#ifndef player_HPP
#define player_HPP

#import <iostream>
#import "player.hpp"
#import "room.hpp"

using namespace std;
class Player {
public:
    Room * location;
    Player(Room *maze);
    void move(int);
    int getNewDir(char*);
};

#endif
