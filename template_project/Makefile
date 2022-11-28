
#
# OS flags
#
ifeq ($(OS),Windows_NT)
	TARGET_OS := Windows
else 
	TARGET_OS := $(shell uname)
endif

#
# Compiler setup
#
CC=gcc
CFLAGS=-std=c99 $(COMPILER_FLAGS)
CWARNINGS=-Werror -Wall -Wextra -Wpedantic -Wfatal-errors

#
# Executables
#
EXE = game
TEST_EXE = test

#
# Directory definitions
#
BIN_ROOT = .bin
BIN = $(BIN_ROOT)/$(TARGET_OS)
INCLUDES = -I. -Isrc/

OBJ_ROOT = .obj
OBJ_TEST_ROOT = .obj_test
OBJ = $(OBJ_ROOT)/$(TARGET_OS)
OBJ_TEST = $(OBJ_TEST_ROOT)/$(TARGET_OS)

SRC = src
SRC_TEST = tests

DEPENDS=.depends

#
# Misc sourcing of files
#
SOURCES := $(wildcard $(SRC)/*.c)
SOURCES_TEST := $(wildcard $(SRC_TEST)/*.c)

OBJECTS := $(patsubst $(SRC)%.c, $(OBJ)/%.o, $(SOURCES)) 
OBJECTS_TEST := $(patsubst $(SRC)%.c, $(OBJ_TEST)/%.o, $(SOURCES)) $(patsubst $(SRC_TEST)%.c, $(OBJ_TEST)/%.o, $(SOURCES_TEST))



#
# Compile obj files
#

%.d : $(SRC)/%.c
	$(CC) -M $< > $@
	@$(CC) -M $< -MT $*.d >> $@  


$(OBJ)/%.o: $(SRC)/%.c Makefile
	$(CC) $(CFLAGS) $(CWARNINGS) $(INCLUDES) -c $< -o $@ $(DEFINES)

$(OBJ_TEST)/%.o: $(SRC_TEST)/%.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -Itests/ -c $< -o $@ $(DEFINES) -DUNIT_TEST

# Compile all obj files for tests, see https://github.com/yshui/test.h
$(OBJ_TEST)/%.o: $(SRC)/%.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -DUNIT_TEST

all: mkdirs $(OBJECTS) link_program

test: mkdirs $(OBJECTS_TEST) link_tests execute_test FORCE

#
# Linking
#
LINKS = $(LIBRARIES) $(PLATFORM_LINKS) -lm -ldl 

link_program:
	$(CC) $(OBJECTS) -o $(BIN)/$(EXE) $(LINKS) 

link_tests:
	$(CC) $(OBJECTS_TEST) -MD -o $(BIN)/$(TEST_EXE) $(LINKS)

depends:
	-@mkdir -p $(DEPENDS)
	echo "fin"

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
# Clean directories
#
.PHONY: clean
clean:
	-@rm -rdf $(DEPENDS)
	-@rm -rdf $(BIN_ROOT)
	-@rm -rdf $(OBJ_ROOT)
	-@rm -rdf $(OBJ_TEST_ROOT)

#
# Ensure all directories exist
#
.PHONY: mkdirs
mkdirs:
	-@mkdir -p $(DEPENDS)
	-@mkdir -p $(BIN_ROOT) 
	-@mkdir -p $(OBJ_ROOT)
	-@mkdir -p $(OBJ_TEST_ROOT)
	-@mkdir -p $(BIN)
	-@mkdir -p $(OBJ)
	-@mkdir -p $(OBJ_TEST)

#
# Empty command to always run
#
FORCE: