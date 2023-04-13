CC=gcc
CFLAGS=-Wall -g -pedantic
SRC_DIR=./src
BIN_DIR=./bin
OBJ_DIR=./obj
DATA_DIR=./data
MAIN_DEPENDENCIES=$(SRC_DIR)/main.c

build: create_bin_dir $(BIN_DIR)/main
	@echo Building...

$(BIN_DIR)/main: $(MAIN_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(SRC_DIR)/main.c -lm -pthread

# Build dirs
create_bin_dir:
	@$(shell mkdir -p $(BIN_DIR))

.PHONY: clean_bin clean
clean_bin:
	rm -rf $(BIN_DIR)/*

clean: clean_bin