#include "input_manager.hpp"

InputManager * InputManager::m_pInstance = nullptr;

InputManager * InputManager::Instance() {
    if (!m_pInstance) m_pInstance = new InputManager;
    return m_pInstance;
}

bool InputManager::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return false;
                break;
                
            case SDL_KEYDOWN:
                onKeyDown(event);
                break;
                
            case SDL_KEYUP:
                onKeyUp(event);
                break;
                
            default:
                break;
        }
    }
    return true;
}

void InputManager::onKeyUp(SDL_Event& event) {
    
    
    switch (event.button.button) {
        case codeUp:
            m_buttonStates[up] = false;
            m_keyUsed[up] = false;
            break;
        case codeDown:
            m_buttonStates[down] = false;
            m_keyUsed[down] = false;
            break;
        case codeLeft:
            m_buttonStates[leftD] = false;
            m_keyUsed[leftD] = false;
            break;
        case codeRight:
            m_buttonStates[rightD] = false;
            m_keyUsed[rightD] = false;
            break;
        default:
            break;
    }
}

void InputManager::onKeyDown(SDL_Event & event) {
    
}

bool InputManager::isKeyDown(SDL_Scancode key) {
    return true;
}
