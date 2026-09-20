CC      = clang
CFLAGS  = -Wall -Wextra -g -std=c11 -Iinclude -I/opt/homebrew/include/SDL2
LDFLAGS = -lSDL2 -L/opt/homebrew/lib

SRC_DIR   = src
BUILD_DIR = build
BIN_DIR   = bin
TARGET    = $(BIN_DIR)/raycast

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
