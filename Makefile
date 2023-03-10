CC=gcc
CFLAGS=-Wall -g -pedantic
SRC_DIR=./src
BIN_DIR=./bin
OBJ_DIR=./obj
DATA_DIR=./data
MAIN_OBJECTS=$(OBJ_DIR)/file.o $(OBJ_DIR)/leibniz.o $(OBJ_DIR)/process.o
MAIN_DEPENDENCIES=$(SRC_DIR)/Process/process.h \
	$(MAIN_OBJECTS) $(SRC_DIR)/main.c

build: create_obj_dir create_bin_dir create_data_dir $(BIN_DIR)/main
	@echo Building...

$(BIN_DIR)/main: $(MAIN_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(SRC_DIR)/main.c $(MAIN_OBJECTS) -lm

$(OBJ_DIR)/process.o: $(SRC_DIR)/Process/process.h  $(SRC_DIR)/Leibniz/leibniz.h $(SRC_DIR)/File/file.h \
	$(SRC_DIR)/Process/process.c
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/process.o -c $(SRC_DIR)/Process/process.c -lm

$(OBJ_DIR)/file.o: $(SRC_DIR)/File/file.h $(SRC_DIR)/File/file.c
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/file.o -c $(SRC_DIR)/File/file.c -lm

$(OBJ_DIR)/leibniz.o: $(SRC_DIR)/Leibniz/leibniz.h $(SRC_DIR)/Leibniz/leibniz.c
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/leibniz.o -c $(SRC_DIR)/Leibniz/leibniz.c -lm

# Build dirs
create_bin_dir:
	@$(shell mkdir -p $(BIN_DIR))

create_obj_dir:
	@$(shell mkdir -p $(OBJ_DIR))

create_data_dir:
	@$(shell mkdir -p $(DATA_DIR))
	@$(shell mkdir -p $(DATA_DIR)/two_process)
	@$(shell mkdir -p $(DATA_DIR)/four_process)

.PHONY: clean_obj clean_data clean_bin clean clean_all
clean_obj:
	rm -rf $(OBJ_DIR)/*

clean_data:
	rm -rf $(DATA_DIR)/*

clean_bin:
	rm -rf $(BIN_DIR)/*

clean: clean_bin clean_obj

clean_all: clean clean_data
