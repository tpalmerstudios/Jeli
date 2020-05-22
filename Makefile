CXX = g++
IDIR = ./include
STBDIR = ./stb
SDL2CFLAGS := $(shell sdl-config --cflags)
SDL2LIBS := $(shell sdl-config --libs)
CXXFLAGS = -Wall -pedantic -std=c++17 -I$(IDIR) -I$(STBDIR) $(SDL2CFLAGS) $(SDL2LIBS) -g
ODIR = src/obj

_DEPS = framebuffer.h geo-prims.h map.h overlay.h player.h render.h sprite.h textures.h utils.h
DEPS = $(patsubst %, $(INCLUDE)/%, $(_DEPS))

_OBJ = framebuffer.o geo-prims.o gui.o map.o render.o sprite.o textures.o utils.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

jeli: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	-rm $(ODIR)/*.o
	-rm jeli

