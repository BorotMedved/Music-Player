CC = gcc
WINDRES = windres

CFLAGS = -Wall -Wextra -std=c11 -DSDL_MAIN_HANDLED
SDLFLAGS = -IC:/msys64/ucrt64/include/SDL2
LDFLAGS = -LC:/msys64/ucrt64/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer -lpsapi -mwindows

TARGET = music_player.exe
SRC = Data/main.c
RES = icon.o

all: $(TARGET)

$(TARGET): $(SRC) $(RES)
	$(CC) $(CFLAGS) $(SDLFLAGS) $(SRC) $(RES) -o $(TARGET) $(LDFLAGS)

$(RES): icon.rc
	$(WINDRES) icon.rc -o $(RES)

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(TARGET) $(RES) 2>nul

.PHONY: all run clean