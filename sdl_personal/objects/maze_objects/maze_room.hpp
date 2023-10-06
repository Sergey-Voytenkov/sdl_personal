#ifndef ROOM_INSTANCE_HPP
#define ROOM_INSTANCE_HPP
#include "libraries.hpp"
#include "sdl_object.hpp"

enum Dirs {
    north = 0,
    south = 1,
    east = 2,
    west = 3,
    sizeOfDirs
};

class MazeRoom: public SDLObject{
public:
    /**Include LoaderParams along with the original X and Y position in the Rooms structure, and roomNumber**/
    MazeRoom(const LoaderParams * params) : SDLObject(params) {}
    ~MazeRoom() {
        m_id = 0;
        m_roomX = m_roomY = 0;
        m_pNorth = m_pSouth = m_pEast = m_pWest = nullptr;
        coordinates_calculated = false;
        initialPositionCalculated = false;
    };
    
    /**Update the cords of the screen position in instance*/
    void draw();
    void update();
    void clean();
    
    void setId(int);
    int getId();
    
    bool setData(int * data);
    int* getData();
    
    void setRoom(Dirs, MazeRoom*);
    MazeRoom* getRoom(Dirs);
    
    std::pair<int, int> getRoomCords();
    void setRoomCords(int, int);

    void updateCords(float x, float y);
    std::pair<float, float> getCords();
    
    //GOT TO ADD
    std::pair<int, int> getDimensions();
    void setDimensions(int, int);

    /**For Room Cords**/
    bool coordinates_calculated;
    bool initialPositionCalculated;
    
private:
    int m_id;
    int m_data[Dirs::sizeOfDirs];
    MazeRoom *m_pNorth, *m_pSouth, *m_pEast, *m_pWest;
    int m_roomX, m_roomY;
};

#endif
