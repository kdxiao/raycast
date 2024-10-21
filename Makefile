CC = clang
CFLAGS = -Wall -Wextra -g -std=c11 -I/opt/homebrew/include/SDL2 
LDFLAGS = -lSDL2 -L/opt/homebrew/lib $(sdl2-config --cflags --libs)

OBJS = map.o player.o init.o raycaster.o main.o 

TARGET = raycast

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile map.c
map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

# Compile player.c
player.o: player.c player.h map.h
	$(CC) $(CFLAGS) -c player.c

init.o: init.c init.h
	$(CC) $(CFLAGS) -c init.c

raycaster.o: raycaster.c raycaster.h map.h player.h
	$(CC) $(CFLAGS) -c raycaster.c

# Compile main.c
main.o: main.c map.h player.h init.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
