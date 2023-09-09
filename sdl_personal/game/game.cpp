#include "game.hpp"
/**Initializes Game components such as SDL, Image, and so on.**/
Game * Game::m_pInstance = nullptr;

Game * Game::Instance() {
    if (!m_pInstance) m_pInstance = new Game();
    return m_pInstance;
}

bool Game::init(int posX, int posY, int width, int height, const char * identifier, bool fullscreen) {
    if (width < 1 || height < 1) {
        cout << "Incorrect inputs. Both width and height must be greater than 1." << endl;
        return false;
    }
    
    posX = (posX < 0) ? 0 : posX;
    posY = (posY < 0) ? 0 : posY;
    
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "Failed to Initialize -> " << SDL_GetError() << endl;
        return false;
    }
    
    uint32_t flag = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;
    m_pWindow = SDL_CreateWindow(identifier, posX, posY, width, height, flag);
    if (!m_pWindow) {
        cout << "Failed to initialize SDL_Window. " << SDL_GetError() << endl;
        return false;
    }
    
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!m_pRenderer) {
        cout << "Failed to create a Accelerated Renderer. " << SDL_GetError() << endl;
        cout << "Attempting Software Renderer... ";
        
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
        if (m_pRenderer)
            cout << "Succeded.";
        else {
            cout << "Unable to create Renderer. " << SDL_GetError() << endl;
            return false;
        }
    }
    
    g_bRunning = true;
    
    TextureManager::Instance()->setRenderer(m_pRenderer);
    if (!TextureManager::Instance()->load_image_resize("../ascii_art/assets/image.jpeg", "ascii", width, height))
        return false;
    
    AsciiArt::Instance()->load_font(m_pRenderer, 8, SDL_Color { 0, 0, 0 });
    AsciiArt::Instance()->calculate_map("ascii", (int)AsciiArt::Instance()->getFont()->w/AsciiArt::Instance()->getCharacterWidth(), AsciiArt::Instance()->getFont()->h);
    AsciiArt::Instance()->create_ascii_art();
    
    m_Objects.push_back(new AsciiArtObject(new LoaderParams(0, 0,  width, height, "ascii")));
    
    return true;
}


/**Handles on input requests**/

bool Game::handle_input() { return true; }

/**Handles updating objects to new positions**/

bool Game::update() { return true; }

/**Handles renderering to screen**/

bool Game::render() { return true; }


/**Cleanup process**/

void Game::clean() {
    //TextureManager::destroy();
    
    if (m_pWindow)
        SDL_DestroyWindow(m_pWindow);
    
    if (m_pRenderer)
        SDL_DestroyRenderer(m_pRenderer);
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

