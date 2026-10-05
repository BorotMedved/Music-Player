CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -DSDL_MAIN_HANDLED
SDLFLAGS = $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer

TARGET = music_player
SRC = Data/main.c Data/sound.c Data/textures.c Data/window.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SDLFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
