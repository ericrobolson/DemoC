
############
# OS flags #
############

ifeq ($(OS),Windows_NT)
	TARGET_OS := Windows
else 
	TARGET_OS := $(shell uname)
endif

#
# Compiler
#
CC=gcc
CFLAGS=-std=c99 $(COMPILER_FLAGS)
CWARNINGS=-Werror -Wall -Wextra -Wpedantic -Wfatal-errors

#
# EXEs
#
EXE = game
TEST_EXE = test

#
# Directories
#
BIN_ROOT = .bin
BIN = $(BIN_ROOT)/$(TARGET_OS)
INCLUDE = include
INCLUDES = -I$(INCLUDE)

RES = res

OBJ_ROOT = .obj
OBJ_TEST_ROOT = .obj_test
OBJ = $(OBJ_ROOT)/$(TARGET_OS)
OBJ_TEST = $(OBJ_TEST_ROOT)/$(TARGET_OS)

SRC = src
SRC_EXTERN = src_extern

#
# Misc sourcing of files
#
SOURCES := $(wildcard $(SRC)/*.c)
SOURCES_EXT := $(wildcard $(SRC_EXTERN)/*.c)

OBJECTS_EXT := $(patsubst $(SRC_EXTERN)%.c, $(OBJ)/%.o, $(SOURCES_EXT))
OBJECTS := $(OBJECTS_EXT) $(patsubst $(SRC)%.c, $(OBJ)/%.o, $(SOURCES)) 
OBJECTS_TEST := $(OBJECTS_EXT) $(patsubst $(SRC)%.c, $(OBJ_TEST)/%.o, $(SOURCES))


#
# Things to always do
#
all: mkdirs $(OBJECTS) link_program copy_files

#
# Tests
#
test: mkdirs $(OBJECTS_TEST) link_tests execute_test FORCE

#
# Compile all obj files
#
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(CWARNINGS) $(INCLUDES) -c $< -o $@ $(DEFINES)

#
# Compile all extern obj files, no warnings
#
$(OBJ)/%.o: $(SRC_EXTERN)/%.c
	$(CC) $(CFLAGS) -Wfatal-errors $(INCLUDES) -c $< -o $@ $(DEFINES)

#
# Compile all obj files for tests, see https://github.com/yshui/test.h
#
$(OBJ_TEST)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -DUNIT_TEST

#
# Copy files
#
copy_files: copy_res
	$(SDL2_COPY_BIN)
	$(SDL2_COPY_README)

$(RES)/%.scm:
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo $@
#	tr -s $@ < $@

SCHEME_FILES := $(wildcard $(RES)/*.scm)


copy_res: $(SCHEME_FILES)
	rsync -a --progress --update --times --verbose $(RES)/* $(BIN)

#
# Linking
#
LINKS = $(LIBRARIES) $(PLATFORM_LINKS) -lm -ldl 

link_program:
	$(CC) $(OBJECTS) -o $(BIN)/$(EXE) $(LINKS)

link_tests:
	$(CC) $(OBJECTS_TEST) -o $(BIN)/$(TEST_EXE) $(LINKS)

#
# Run tests
#
execute_test:
	./$(BIN)/$(TEST_EXE)

#
# Builds + runs the program
#
CWD = $(shell pwd)
run: all
	clear
	cd $(BIN) && ./$(EXE);

#
# Clean task
# 
.PHONY: clean
clean:
	rm -R $(BIN)
	rm -R $(OBJ)
	rm -R $(OBJ_TEST)

.PHONY: clean_all
clean_all:
	rm -R $(BIN_ROOT)
	rm -R $(OBJ_ROOT)
	rm -R $(OBJ_TEST_ROOT)

#
# Make directories
#
.PHONY: mkdirs
mkdirs:
	-mkdir $(BIN_ROOT)
	-mkdir $(OBJ_ROOT)
	-mkdir $(OBJ_TEST_ROOT)
	-mkdir $(BIN)
	-mkdir $(OBJ)
	-mkdir $(OBJ_TEST)

#
# Empty command to always run
#
FORCE:
