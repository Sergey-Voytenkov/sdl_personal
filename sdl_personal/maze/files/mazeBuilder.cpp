#include "mazeBuilder.hpp"

#define DATASIZE 100

using namespace std;


MazeBuilder::MazeBuilder(const char * mazeFileName, int roomWidth, int roomHeight, string identifier) {
    roomCount = readRoomCount(mazeFileName);
    m_pRooms = buildRooms(mazeFileName, roomCount, roomWidth, roomHeight, identifier);
}


std::vector<MazeRoom*>* MazeBuilder::buildRooms(const char * mazeFileName, int roomCount, int roomWidth, int roomHeight, string identifier) {
    // String is required for ifstream to function
    string mazeFileNameStr(mazeFileName);
    ifstream mazeFile(mazeFileNameStr);
    
    char buf[DATASIZE];
    
//    Node * Rooms = (Node*)malloc(sizeof(Node)*roomCount);
    std::vector<MazeRoom*>* pRooms = prebuildRooms(roomCount, roomWidth, roomHeight, identifier);
    for (int i = 0; i < roomCount; ++i) {
        mazeFile.getline(buf, DATASIZE);
        char ** ppSnippets = split(buf);
        parseRoomData(pRooms->at(i), ppSnippets);
        
        //+1 for roomId, everything else for directions
        for (int j = 0; j < Dirs::sizeOfDirs+1; j++) free(ppSnippets[j]);
        free(ppSnippets);
        
        cout << "Built room #" << i << " with ID " << pRooms->at(i)->getId() <<endl;
    };
    
    for (int i = 0; i < roomCount; ++i)
        searchAndAssignDirections(pRooms, i, roomCount);
    
    pRooms->at(0)->coordinates_calculated = true;
    calculateNeighborCoordinates(pRooms->at(0));
    
    return pRooms;
};
                                    
std::vector<MazeRoom*>* MazeBuilder::prebuildRooms(int sizeCount, int width, int height, string identifier) {
    std::vector<MazeRoom*>* pRooms = new std::vector<MazeRoom*>;
    for (int i = 0; i < sizeCount; i++)
        pRooms->push_back(new MazeRoom(new LoaderParams(0, 0, width, height, identifier)));
    
    for (int i = 0; i < sizeCount; i++) {
        pRooms->at(i)->setDimensions(width, height);
        pRooms->at(i)->setRoomCords(0, 0);
    }
    
    return pRooms;
}

int MazeBuilder::readRoomCount(const char *mazeFileName) {
    int roomCount = 0;
    
    //    char strbuf[DATASIZE];
    // has to be a string for getline() to work.
    string strbuf;
    
    ifstream mazeFile(mazeFileName);
    if(!mazeFile.good()) {
        cout << "File is missing." << endl;
        return -1;
    };
    
    while (!mazeFile.eof() && getline(mazeFile, strbuf) && mazeFile.good()) {
        ++roomCount;
        cout << strbuf << endl;
    };
    
    mazeFile.close();
    return roomCount;
}

void MazeBuilder::parseRoomData(MazeRoom* pRoom, char ** pSnippets) {
    int ids[Dirs::sizeOfDirs] = {0};
    
    // Calculates room IDs
    for (int i = 0; i < Dirs::sizeOfDirs+1; i++)
        for (int j = 0; j < strlen(pSnippets[i]); j++)
            ids[i] = (ids[i]*10) + (pSnippets[i][j]-48);
    
    // Sets room ID
    pRoom->setId(ids[0]);
    
    // Sets ajacent room IDs
    int * pData = pRoom->getData();
    for (int i = 0; i < Dirs::sizeOfDirs; i++) {
        pData[i] = ids[i+1];
    };
};

char ** MazeBuilder::split(char * data) {
    char ** ppSnipets = (char**)malloc(sizeof(char*)*(Dirs::sizeOfDirs+1));
    int i = 0;
    int s = 0;
    while (s < Dirs::sizeOfDirs+1) {
        while (i < strlen(data)) {
            int j = i;
            while (data[j] != ',' && data[j] != '\n') j++;
            int size = j - i;
            ppSnipets[s] = (char*)malloc(sizeof(char)*size+1);
            
            int k = 0;
            while (i < j) ppSnipets[s][k++] = data[i++];
            ppSnipets[s++][k] = 0;
            i++;
        }
    }
    return ppSnipets;
}

void MazeBuilder::searchAndAssignDirections(std::vector<MazeRoom*>* pRooms, int roomId, int roomCount) {
    // Data[0] is roomId.
    int * data = pRooms->at(roomId)->getData();
    cout << "Room ID=" << pRooms->at(roomId)->getId() << " Data: ";
    for (int i = 0; i < 4; i++) cout << data[i] << ',';
    cout << endl;

    pRooms->at(roomId)->setRoom(Dirs::north, findRoom(data[0], pRooms, roomCount));
    pRooms->at(roomId)->setRoom(Dirs::south, findRoom(data[0], pRooms, roomCount));
    pRooms->at(roomId)->setRoom(Dirs::east, findRoom(data[0], pRooms, roomCount));
    pRooms->at(roomId)->setRoom(Dirs::west, findRoom(data[0], pRooms, roomCount));
    
    cout << " North: " << pRooms->at(roomId)->getRoom(Dirs::north);
    cout << " South: " << pRooms->at(roomId)->getRoom(Dirs::south);
    cout << " East: " << pRooms->at(roomId)->getRoom(Dirs::east);
    cout << " West: " << pRooms->at(roomId)->getRoom(Dirs::west);
    
    cout << endl;
}

MazeRoom* MazeBuilder::findRoom(int roomNum, std::vector<MazeRoom*>* pRooms, int roomCount) {
    for (int i = 0; i < roomCount || i < pRooms->size(); ++i)
        if (pRooms->at(i)->getId() == roomNum)
            return pRooms->at(i);
    
    return NULL;
};

//void MazeBuilder::destroyRooms() {
////    free(rooms);
//}

void MazeBuilder::calculateNeighborCoordinates(MazeRoom* pRoom) {
    std::pair<int, int> tempCords;
    
    if (pRoom->getRoom(Dirs::north) != nullptr && pRoom->getRoom(Dirs::north)->coordinates_calculated) {
        tempCords= pRoom->getRoomCords();
        pRoom->getRoom(Dirs::north)->setRoomCords(tempCords.first, tempCords.second + 1);
        pRoom->getRoom(Dirs::north)->coordinates_calculated = true;
        calculateNeighborCoordinates(pRoom->getRoom(Dirs::north));
    }
    
    if (pRoom->getRoom(Dirs::south) != nullptr && pRoom->getRoom(Dirs::south)->coordinates_calculated) {
        tempCords = pRoom->getRoomCords();
        pRoom->getRoom(Dirs::south)->setRoomCords(tempCords.first, tempCords.second - 1);
        pRoom->getRoom(Dirs::south)->coordinates_calculated = true;
        calculateNeighborCoordinates(pRoom->getRoom(Dirs::south));
    }
        
    if (pRoom->getRoom(Dirs::east) != nullptr && pRoom->getRoom(Dirs::east)->coordinates_calculated) {
        tempCords = pRoom->getRoomCords();
        pRoom->getRoom(Dirs::east)->setRoomCords(tempCords.first + 1, tempCords.second);
        pRoom->getRoom(Dirs::east)->coordinates_calculated = true;
        calculateNeighborCoordinates(pRoom->getRoom(Dirs::east));
    }
    
    if (pRoom->getRoom(Dirs::west) != nullptr && pRoom->getRoom(Dirs::west)->coordinates_calculated) {
        tempCords = pRoom->getRoomCords();
        pRoom->getRoom(Dirs::west)->setRoomCords(tempCords.first + 1, tempCords.second);
        pRoom->getRoom(Dirs::west)->coordinates_calculated = true;
        calculateNeighborCoordinates(pRoom->getRoom(Dirs::west));
    }

}

MazeBuilder::~MazeBuilder() {
//    destroyRooms();
}



/*
 MazeBuilder::MazeBuilder(char * mazeFileName) {
     roomCount = readRoomCount(mazeFileName);
     rooms = buildRooms(mazeFileName, roomCount);
 }


 Room * MazeBuilder::buildRooms(char * mazeFileName, int roomCount) {
     // String is required for ifstream to function
     string mazeFileNameStr(mazeFileName);
     ifstream mazeFile(mazeFileNameStr);
     
     char buf[DATASIZE];
     
 //    Node * Rooms = (Node*)malloc(sizeof(Node)*roomCount);
     Room * Rooms = new Room[roomCount];
     for (int i = 0; i < roomCount; ++i) {
         Rooms[i].north = NULL;
         Rooms[i].south = NULL;
         Rooms[i].east = NULL;
         Rooms[i].west = NULL;
         
         Rooms[i].x = Rooms[i].y = 0;
         Rooms[i].coordinates_calculated = false;
         
         mazeFile.getline(buf, DATASIZE);
         char ** snippets = split(buf);
         parseRoomData(&Rooms[i], snippets);
         
         for (int j = 0; j < 5; j++) free(snippets[j]);
         free(snippets);
         
         cout << "Built room #" << i << " with ID " << Rooms[i].id <<endl;
     };
     
     for (int i = 0; i < roomCount; ++i)
         searchAndAssignDirections(Rooms, i, roomCount);
     
     Rooms[0].coordinates_calculated = true;
     calculateNeighborCoordinates(Rooms);
     
     return Rooms;
 };

 int MazeBuilder::readRoomCount(char *mazeFileName) {
     int roomCount = 0;
     
     //    char strbuf[DATASIZE];
     // has to be a string for getline() to work.
     string strbuf;
     
     ifstream mazeFile(mazeFileName);
     if(!mazeFile.good()) {
         cout << "File is missing." << endl;
         return -1;
     };
     
     while (!mazeFile.eof() && getline(mazeFile, strbuf) && mazeFile.good()) {
         ++roomCount;
         cout << strbuf << endl;
     };
     
     mazeFile.close();
     return roomCount;
 }

 void MazeBuilder::parseRoomData(Room * room, char ** snippets) {
     int ids[5] = {0,0,0,0,0};
     
     // Calculates room IDs
     for (int i = 0; i < 5; i++)
         for (int j = 0; j < strlen(snippets[i]); j++)
             ids[i] = (ids[i]*10) + (snippets[i][j]-48);
     
     // Sets room ID
     room->id = ids[0];
     
     // Sets ajacent room IDs
     for (int i = 0; i < 4; i++) {
         room->data[i] = ids[i+1];
     };
 };

 char ** MazeBuilder::split(char * data) {
     char ** snippets = (char**)malloc(sizeof(char*)*5);
     int i = 0;
     int s = 0;
     while (s < 5) {
         while (i < strlen(data)) {
             int j = i;
             while (data[j] != ',' && data[j] != '\n') j++;
             int size = j - i;
             snippets[s] = (char*)malloc(sizeof(char)*size+1);
             
             int k = 0;
             while (i < j) snippets[s][k++] = data[i++];
             snippets[s++][k] = 0;
             i++;
         }
     }
     return snippets;
 }

 void MazeBuilder::searchAndAssignDirections(Room * Rooms, int roomIDX, int roomCount) {
     // Data[0] is roomId.
     int * data = Rooms[roomIDX].data;
     cout << "Room ID=" << Rooms[roomIDX].id << " Data: ";
     for (int i = 0; i < 4; i++) cout << data[i] << ',';
     cout << endl;
     
     Rooms[roomIDX].north = findRoom(data[0], Rooms, roomCount);
     Rooms[roomIDX].south = findRoom(data[1], Rooms, roomCount);
     Rooms[roomIDX].east = findRoom(data[2], Rooms, roomCount);
     Rooms[roomIDX].west = findRoom(data[3], Rooms, roomCount);
     
     cout << " North: " << Rooms[roomIDX].north;
     cout << " South: " << Rooms[roomIDX].south;
     cout << " East: " << Rooms[roomIDX].east;
     cout << " West: " << Rooms[roomIDX].west;
     
     cout << endl;
 }

 Room * MazeBuilder::findRoom(int roomNum, Room* rooms, int roomCount) {
     for (int i = 0; i < roomCount; ++i)
         if (rooms[i].id == roomNum)
             return &rooms[i];
     
     return NULL;
 };

 void MazeBuilder::destroyRooms() {
     free(rooms);
 }

 void MazeBuilder::calculateNeighborCoordinates(Room *room) {
     if (room->north && !room->north->coordinates_calculated) {
         room->north->x = room->x;
         room->north->y = room->y + 1;
         room->north->coordinates_calculated = true;
         calculateNeighborCoordinates(room->north);
     }
     if (room->south && !room->south->coordinates_calculated) {
         room->south->x = room->x;
         room->south->y = room->y - 1;
         room->south->coordinates_calculated = true;
         calculateNeighborCoordinates(room->south);
     }
     if (room->east && !room->east->coordinates_calculated) {
         room->east->x = room->x + 1;
         room->east->y = room->y;
         room->east->coordinates_calculated = true;
         calculateNeighborCoordinates(room->east);
     }
     if (room->west && !room->west->coordinates_calculated) {
         room->west->x = room->x - 1;
         room->west->y = room->y;
         room->west->coordinates_calculated = true;
         calculateNeighborCoordinates(room->west);
     }
 }

 MazeBuilder::~MazeBuilder() {
     destroyRooms();
 }
*/
