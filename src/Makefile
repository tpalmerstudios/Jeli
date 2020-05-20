CXX = g++
IDIR = ../include
STBDIR = ../stb
SDL2CFLAGS = -I/usr/include/SDL2 -D_REENTRANT1
SDL2LIBS = -L/usr/lib -pthread -lSDL2
CXXFLAGS = -Wall -pedantic -std=c++17 -I$(IDIR) -I$(STBDIR) $(SDL2CFLAGS) $(SDL2LIBS) -g
ODIR = obj

_DEPS = framebuffer.h map.h overlay.h player.h render.h sprite.h textures.h utils.h
DEPS = $(patsubst %, $(INCLUDE)/%, $(_DEPS))

_OBJ = framebuffer.o gui.o map.o render.o sprite.o textures.o utils.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

jeli: $(OBJ)
	$(CXX) -o ../$@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	-rm $(ODIR)/*.o
	-rm ../jeli

