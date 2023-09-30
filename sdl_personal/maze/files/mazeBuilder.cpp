#include "mazeBuilder.hpp"

#define DATASIZE 100

using namespace std;


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
