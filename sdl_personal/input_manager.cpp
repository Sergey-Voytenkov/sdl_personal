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
            m_buttonStates[upD] = false;
            m_keyUsed[upD] = false;
            break;
        case codeDown:
            m_buttonStates[downD] = false;
            m_keyUsed[downD] = false;
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
    switch (event.button.button) {
    case codeUp:
        m_buttonStates[upD] = true;
        break;
    case codeDown:
        m_buttonStates[downD] = true;
        break;
    case codeLeft:
        m_buttonStates[leftD] = true;
        break;
    case codeRight:
        m_buttonStates[rightD] = true;
        break;
    default:
        break;
    }
    
}

bool InputManager::isKeyDown(directionCodes key) {
    return isKeyDown(key, 0);
}

bool InputManager::isKeyDown(directionCodes key, bool setGivenKeyDown) {
    switch (key) {
    case codeUp:
        m_keyUsed[upD] = setGivenKeyDown ? true : m_keyUsed[upD];
        return m_buttonStates[upD];
    case codeDown:
        m_keyUsed[downD] = setGivenKeyDown ? true : m_keyUsed[downD];
        return m_buttonStates[downD];
    case codeLeft:
        m_keyUsed[leftD] = setGivenKeyDown ? true : m_keyUsed[leftD];
        return m_buttonStates[leftD];
    case codeRight:
        m_keyUsed[rightD] = setGivenKeyDown ? true : m_keyUsed[rightD];
        return m_buttonStates[rightD];
    default:
        return false;
    }

    return false;
}

bool InputManager::wasKeyUsed(directionCodes key) {
    switch (key) {
    case codeUp:
        return m_keyUsed[upD];
    case codeDown:
        return m_keyUsed[downD];
    case codeLeft:
        return m_keyUsed[leftD];
    case codeRight:
        return m_keyUsed[rightD];
    default:
        return false;
    }

    return false;
}

void InputManager::setKeyUsed(directionCodes key) {
    switch (key) {
    case codeUp:
        m_keyUsed[codeUp] = true;
        break;
    case codeDown:
        m_keyUsed[codeDown] = true;
        break;
    case codeLeft:
        m_keyUsed[codeLeft] = true;
        break;
    case codeRight:
        m_keyUsed[codeRight] = true;
        break;
    default:
        break;
    }
}
