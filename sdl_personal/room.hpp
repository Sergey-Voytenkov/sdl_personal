#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>

class Room {
public:
    int id;
    int data[4];
    Room *north, *south, *east, *west;
    
    int x;
    int y;
    bool coordinates_calculated;
    void print();
};

#endif
