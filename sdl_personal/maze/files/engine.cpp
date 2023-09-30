//#import "engine.hpp"
//#import "graphicsManager.hpp"
//
//Engine::Engine(char *MAZE_MAP_FILENAME) {
//    this->maze = new MazeBuilder(MAZE_MAP_FILENAME);
//    this->player = new Player(this->maze->rooms);
//};
//
//void Engine::run() {
////    bool quit = false;
////     cout << "Weclome to the game, you are in the first room. Get to the last." << endl;
////     cout << "Make it out :D" << endl;
////     while (!quit) {
////         player->location->print();
////         cout << "Where next? | ";
////         char * input = terInput();
////         int direction = player->getNewDir(input);
////         if (direction > 3) quit = true;
////         else if (direction < 0) cout << "Cant move that way!" << endl;
////         else player->move(direction);
////    }
//    
//    Graphics graphics(300, 300);
//    graphics.run();
//    
//    
//}
//
//char * Engine::terInput() {
//    char buf[10];
//    cin >> buf;
//    cout << endl;
//
//    char * input = (char*)malloc(strlen(buf)+1);
//    strcpy(input, buf);
//    //input[0] = buf[0];
//    return input;
//}
//
