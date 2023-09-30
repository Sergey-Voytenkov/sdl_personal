#ifndef ROOM_INSTANCE_HPP
#define ROOM_INSTANCE_HPP
#include "libraries.hpp"
#include "sdl_object.hpp"

class MazeRoom: public SDLObject{
public:
    /**Include LoaderParams along with the original X and Y position in the Rooms structure, and roomNumber**/
    MazeRoom(const LoaderParams * params, int roomX, int roomY, int roomNumber) : SDLObject(params), m_roomX(roomX), m_roomY(roomY), m_roomNumber(roomNumber) {}
    ~MazeRoom() {};
    
    /*Update the cords of the instance**/
    void updateCords(float x, float y);
    
    void draw();
    void update();
    void clean();

    bool initialPositionCalculated;

    
private:
    int m_roomX, m_roomY;
    int m_roomNumber;
    
};

#endif
