#include "room.hpp"

void Room::print() {
    int north = this->north ? this->north->id : 0;
    int south = this->south ? this->south->id : 0;
    int east  = this->east  ? this->east->id : 0;
    int west  = this->west  ? this->west->id : 0;

    std::cout << "   N" << north << std::endl;
    std::cout << 'W' << west << " " << this->id << " E" << east << std::endl;
    std::cout << "   S" << south << std::endl;
}
