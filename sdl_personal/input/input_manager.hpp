#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP
#include "../other/libraries.hpp"

using namespace std;

enum directionsCodes {
    codeUp    = SDL_SCANCODE_UP,
    codeDown  = SDL_SCANCODE_DOWN,
    codeLeft  = SDL_SCANCODE_LEFT,
    codeRight = SDL_SCANCODE_RIGHT,
    directionCodeCount
};
enum directions {
    up = 0,
    down = 1,
    leftD = 2, //Their taken by an opperation
    rightD = 3,
    directionCount
};


class InputManager {
public:
    static InputManager * Instance();
    
    bool update();
    
    bool isKeyDown(SDL_Scancode key);
    
    
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
