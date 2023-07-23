PROJECTNAME=missing_semester_pretest
CPPCOMPILER=g++
CPPFLAGS=-Wall -Wextra -I$(IDIR)
CPPFLAGS_TEST=$(CPPFLAGS) -I$(I_TEST_DIR)

IDIR=include
I_TEST_DIR=$(TEST_DIR)/include

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := tests
BIN_TESTS_DIR := $(TEST_DIR)/bin

# List of source files and corresponding object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# for now we will accept to generate .o test files in the <root>/obj
TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRC_FILES))

# this variable will exclude tha main object file from the test rule 
# to avoid conflicting between the doctest main and app main
TEST_FILTER_OUT := $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES))

TARGET := $(BIN_DIR)/$(PROJECTNAME)
TEST_TARGET := $(BIN_TESTS_DIR)/$(PROJECTNAME)

$(TARGET): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CPPCOMPILER) $(CPPFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CPPCOMPILER) $(CPPFLAGS) -c -o $@ $<

$(TEST_TARGET): $(TEST_FILTER_OUT) $(TEST_OBJ_FILES)
	mkdir -p $(BIN_TESTS_DIR)
	$(CPPCOMPILER) $(CPPFLAGS_TEST) -o $@ $^

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

compile: $(TARGET)

start:
	$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(BIN_TESTS_DIR)

test: compile $(TEST_TARGET)
	$(TEST_TARGET)
