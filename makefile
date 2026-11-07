CC = gcc
WINDRES = windres

CFLAGS = -Wall -Wextra -std=c11 -DSDL_MAIN_HANDLED -DSDL_STATIC_LIB $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_mixer)
LDFLAGS = -static -mwindows $(shell pkg-config --static --libs sdl2 SDL2_ttf SDL2_mixer) -lstdc++
TARGET = Player.exe
SRC = Data/main.c Data/sound.c Data/textures.c Data/window.c
RES = icon.o

all: $(TARGET)

$(TARGET): $(SRC) $(RES)
	$(CC) $(CFLAGS) $(SRC) $(RES) -o $(TARGET) $(LDFLAGS)

$(RES): icon.rc
	$(WINDRES) icon.rc -o $(RES)

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(TARGET) $(RES) 2>nul

.PHONY: all run clean