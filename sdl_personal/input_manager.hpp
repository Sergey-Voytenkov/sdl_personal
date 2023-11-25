#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP
#include "libraries.hpp"
using namespace std;

enum directionCodes {
    codeUp    = SDL_SCANCODE_UP,
    codeDown  = SDL_SCANCODE_DOWN,
    codeLeft  = SDL_SCANCODE_LEFT,
    codeRight = SDL_SCANCODE_RIGHT,
    directionCodeCount
};

enum directions {
    upD = 0,
    downD = 1,
    leftD = 2, //Their taken by an opperation
    rightD = 3,
    directionCount
};


class InputManager {
public:
    static InputManager * Instance();
    
    bool update();
    
    //Returns key state, can also set keyUsed state
    bool isKeyDown(directionCodes key, bool setGivenKeyDown);
    //Return only key state
    bool isKeyDown(directionCodes key);
    //Return keyUsed state
    bool wasKeyUsed(directionCodes key);
    //Set keyUsed state
    void setKeyUsed(directionCodes key);
private:
    InputManager() {
        for (int i = 0; i < directionCount; i++) {
            m_buttonStates[i] = false;
            m_keyUsed[i] = false;
        }
    }
    ~InputManager() {}
    
    void onKeyDown(SDL_Event & event);
    void onKeyUp(SDL_Event & event);
    
    
    
    map<int, bool> m_buttonStates;
    map<int, bool> m_keyUsed;
    
    static InputManager * m_pInstance;
    
};

#endif
