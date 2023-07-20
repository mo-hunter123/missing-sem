PROJECTNAME=missing_semester_pretest
CPPCOMPILER=g++
CPPFLAGS=-Wall -Wextra -I$(IDIR)

IDIR=include

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin


# List of source files and corresponding object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET := $(BIN_DIR)/$(PROJECTNAME)

compile: $(TARGET)

$(TARGET): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CPPCOMPILER) $(CPPFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CPPCOMPILER) $(CPPFLAGS) -c -o $@ $<

start:
	$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
