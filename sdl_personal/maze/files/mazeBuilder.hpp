#ifndef mazeBuilder_hpp
#define mazeBuilder_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <cstring>
//#include <algorithm>

#include "SDL2/SDL_image.h"
#include "../../objects/maze_objects/maze_room.hpp"
class MazeBuilder {
public:
    std::vector<MazeRoom*>* m_pRooms;
    int getRoomCount() { return roomCount; }
    MazeBuilder(const char* mazeFileName, int roomWidth, int roomHeight, string textureIdentifier);
    ~MazeBuilder();

private:
   /* void destroyRooms()*/;
    std::vector<MazeRoom*>* buildRooms(const char*, int, int, int, string);
    std::vector<MazeRoom*>* prebuildRooms(int, int, int, string);
    int roomCount;
    
    void parseRoomData(MazeRoom*, char**);
    char** split(char*);
    int readRoomCount(const char*);
    void getDirections(char*, int*);
    void searchAndAssignRoom(MazeRoom*, int);
    void searchAndAssignDirections(std::vector<MazeRoom*>*, int, int);
    void calculateNeighborCoordinates(MazeRoom*);
    MazeRoom* findRoom(int, std::vector<MazeRoom*>*, int);
    
};

//#include "room.hpp"

//using namespace std;
//class MazeBuilder {
//public:
//    Room * rooms;
//    int getRoomCount() { return roomCount; }
//    MazeBuilder(char*);
//    ~MazeBuilder();
//private:
//    Room * buildRooms(char*, int);
//    int roomCount;
//
//    void parseRoomData(Room* , char**);
//    char ** split(char*);
//    int readRoomCount(char*);
//    void getDirections(char*, int*);
//    void searchAndAssignRoom(Room*, int);
//    void searchAndAssignDirections(Room*, int, int);
//    Room * findRoom(int, Room*, int);
//    
//    //void buildRoomRelations(Node*, int);
//    void destroyRooms();
//    void calculateNeighborCoordinates(Room*);
//    
//};



#endif
