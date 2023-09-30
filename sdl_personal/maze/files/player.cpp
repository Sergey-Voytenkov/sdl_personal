#include "player.hpp"

// class Player
Player::Player(Room *maze) {
    this->location = &maze[0];
}

int Player::getNewDir(char *input) {
    switch(input[0]) {
        case 'N':
        case 'n':
            free(input);
            return 0;
        case 'S':
        case 's':
            free(input);
            return 1;
        case 'E':
        case 'e':
            free(input);
            return 2;
        case 'W':
        case 'w':
            free(input);
            return 3;
        case 'X':
        case 'x':
            free(input);
            return 4;
        default:
            free(input);
            return -1;
    }
}
void Player::move(int dir) {
    switch(dir) {
   	 	case 0:
            if (this->location->north == NULL) return;
            (*this).location = (*this).location->north;
//    		if ((*player)->north == NULL) return;
//    		(*player) = (*player)->north;

    		break;
   		case 1:
            if (this->location->south == NULL) return;
            (*this).location = (*this).location->south;
//    		if ((*player)->south == NULL) return;
//    		(*player) = (*player)->south;

    		break;
    	case 2:
            if (this->location->east == NULL) return;
            (*this).location = (*this).location->east;
//    		if ((*player)->east == NULL) return;
//    		(*player) = (*player)->east;

    		break;
    	case 3:
            if (this->location->west == NULL) return;
            (*this).location = (*this).location->west;
//    		if ((*player)->west == NULL) return;
//    		(*player) = (*player)->west;
    };
    return;
};

