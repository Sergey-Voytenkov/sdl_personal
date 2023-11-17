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

    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {
        cout << "Failed to Initialize -> " << SDL_GetError() << endl;
        return false;
    }
    
    if (!Renderer::Instance()->init(posX, posY, width, height, identifier, fullscreen))
    
    
    m_pWindow = Renderer::Instance()->getWindow();
    m_pRenderer = Renderer::Instance()->getRenderer();
    Renderer::Instance()->setScreenSizeReference(width, height);
    TextureManager::Instance()->setRenderer(m_pRenderer);

    SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 70, 50); // RGBA

    g_bRunning = true;
    m_pMaze = Maze::Instance();
        if (!m_pMaze->build()) return false;
    m_pPlayer = m_pMaze->getPlayer();





    std::vector<MazeRoom*>* maze = m_pMaze->getMaze();
    
    // Why does this not work?
    // Isn't m_pMaze a instance of Object?
    // What did I do wrong?
    m_Objects = &maze; 

    


//    TextureManager::Instance()->setRenderer(m_pRenderer);
//    if (!TextureManager::Instance()->load_image_resize("../ascii_art/assets/image.jpeg", "ascii", width, height))
//        return false;
//
//    AsciiArt::Instance()->load_font(m_pRenderer, 8, SDL_Color { 0, 0, 0 });
//    AsciiArt::Instance()->calculate_map("ascii", (int)AsciiArt::Instance()->getFont()->w/AsciiArt::Instance()->getCharacterWidth(), AsciiArt::Instance()->getFont()->h);
//    AsciiArt::Instance()->create_ascii_art();
//
//    m_Objects.push_back(new AsciiArtObject(new LoaderParams(0, 0,  width, height, "ascii")));
//
    return true;
}


/**Handles on input requests**/

bool Game::handle_input() {
    SDL_Event event;
    while(SDL_PollEvent(&event))
        if (event.type == SDL_QUIT) {
            stopRunning();

            clean();
        }
    return true; 
}

/**Handles updating objects to new positions**/

bool Game::update() {
    std::vector<Object*>::iterator it;

    for (it = m_Objects.begin(); it != m_Objects.end(); it++ ) {
        (*it)->update();

    }

    return true;
}

/**Handles renderering to screen**/

bool Game::render() {
    SDL_RenderClear(m_pRenderer);

    std::vector<Object*>::iterator it;
    for (it = m_Objects.begin(); it != m_Objects.end(); it++) {
        (*it)->draw();
    }

    SDL_RenderPresent(m_pRenderer);
    return true;
}


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
