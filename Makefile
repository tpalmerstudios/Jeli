CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17 -g
SDL2CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
SDL2LIBS = -L/usr/lib -pthread -lSDL2
OBJECTS = gui.o render.o map.o framebuffer.o textures.o sprite.o utils.o
HEADERS = framebuffer.h map.h player.h sprite.h textures.h render.h utils.h

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< $(SDL2CFLAGS) $(SDL2LIBS) -o $@

.cpp:
	$(CXX) $(CXXFLAGS) $@.cpp $(SDL2CFLAGS) $(SDL2LIBS) -o $@

jeli: $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(SDL2CFLAGS) $(SDL2LIBS) -o $@

clean:
	-rm *.o jeli
