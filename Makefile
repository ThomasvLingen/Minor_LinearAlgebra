SILENT = @

# Compiler
CC = g++
LD = $(CC)

IMGUI_PATH = libs/imgui

# Compiler flags
# Wall = all warnings
# Wextra = extra warnings
# g = debug symbols
# std=c++11 = C++11
INCLUDE_PATHS = -Isrc/ -I$(IMGUI_PATH)
COMPILER_FLAGS = -Wall -Wextra -g -std=c++11 $(INCLUDE_PATHS)

# Linker flags
# g = debug symbols
LIBS_PATH =
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx -ldl -lGL -lGLU
LINKER_FLAGS = -g

# Files to compile
SRC_PATH = src/
SRC_FILES = $(shell find $(SRC_PATH) -name '*.cpp')
HPP_FILES = $(shell find $(SRC_PATH) -name '*.hpp')
ALL_FILES = $(SRC_FILES) $(HPP_FILES)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Path for the resulting file
BUILD_PATH = build/
RES_PATH = res/
PROGRAM_NAME = LinearAlgebra
EXEC = $(BUILD_PATH)$(PROGRAM_NAME)

# Imgui library
SRC_PATH += ${shell find $(IMGUI_PATH) -name '*.cpp' -not -path '$(IMGUI_PATH)/examples/*' -not -path '$(IMGUI_PATH)/extra_fonts/*'}
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Compile stuff
%.o : %.cpp
	@echo CC $<
	$(SILENT) $(CC) -c $< $(COMPILER_FLAGS) -o $@

$(EXEC) : $(OBJ_FILES)
	@echo
	mkdir -p $(BUILD_PATH)
	@echo LD $@
	$(SILENT) $(LD) $(COMPILER_FLAGS) $(OBJ_FILES) $(LINKER_FLAGS) $(LIBS) -o $(EXEC)
	@echo
	@echo "Moving resources to build"
	cp -r $(RES_PATH) $(BUILD_PATH)
	@echo

all : $(EXEC)

run : $(EXEC)
	$(EXEC)

debug: $(EXEC)
	gdb $(EXEC)

memory_leaks: $(EXEC)
	valgrind --tool=memcheck --leak-check=full $(EXEC)

search_for_tabs: $(SRC_PATH)
	grep -r $$'\t' $(SRC_PATH)

tabs_to_spaces: $(ALL_FILES)
	sed -i $$'s/\t/    /g' $(ALL_FILES)

.PHONY: clean
clean:
	@echo "Cleaning build"
	rm -rf $(shell find $(SRC_PATH) -name '*.o')
	rm -rf $(BUILD_PATH)*
