
DEPS= -I/opt/homebrew/include/ -L/opt/homebrew/cellar/SDL2/2.28.5/lib -lSDL2 -I/opt/homebrew/Cellar/sdl2_image/2.6.3_2/include -L/opt/homebrew/Cellar/sdl2_image/2.6.3_2/lib -lSDL2_image -I/opt/homebrew/Cellar/sdl2_ttf/2.20.2/include -L/opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib -lSDL2_ttf
# main: main.cpp $(DEPS)
# 	cd ../build/
# 	g++ -c ../sdl_personal/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/game/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/game/renderer/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/input/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/vectors/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/maze/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/maze/files*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/objects/maze_objects/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/objects/virtual/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/objects/other/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf
# 	g++ -c ../sdl_personal/texture_manager/*.cpp $(DEPS) -lSDL2 -lSDL2_image -lSDL2_ttf

main:
	g++ -std=c++17 -c -I/opt/homebrew/Cellar/sdl2/2.28.4/include -I/opt/homebrew/Cellar/sdl2_image/2.6.3_2/include -I/opt/homebrew/Cellar/sdl2_ttf/2.20.2/include *.cpp
	g++ -std=c++17 -o main *.o $(DEPS) ../build/

libraries.o: libraries.hpp
	g++ -std=c++17 -c libraries.cpp $(DEPS)

clean:
	rm -f *.o