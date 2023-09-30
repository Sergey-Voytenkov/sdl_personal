#ifndef mazeBuilder_hpp
#define mazeBuilder_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <cstring>
//#include <algorithm>
#include "room.hpp"


using namespace std;
class MazeBuilder {
public:
    Room * rooms;
    int getRoomCount() { return roomCount; }
    MazeBuilder(char*);
    ~MazeBuilder();
private:
    Room * buildRooms(char*, int);
    int roomCount;

    void parseRoomData(Room* , char**);
    char ** split(char*);
    int readRoomCount(char*);
    void getDirections(char*, int*);
    void searchAndAssignRoom(Room*, int);
    void searchAndAssignDirections(Room*, int, int);
    Room * findRoom(int, Room*, int);
    
    //void buildRoomRelations(Node*, int);
    void destroyRooms();
    void calculateNeighborCoordinates(Room*);
    
};

#endif
