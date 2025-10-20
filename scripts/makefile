# Compiler
CXXC = g++

# Paths
SRCP = src/
OBJDIR = obj/
BINDIR = bin/

# Source files
SRC = $(SRCP)main.cpp \
      $(SRCP)SDL2_Event.cpp \
      $(SRCP)SDL2_InitWin.cpp

# Object files (replace src/ with obj/ and .cpp with .o)
OBJ = $(SRC:$(SRCP)%.cpp=$(OBJDIR)%.o)

# SDL2 includes and libs
SDL2I = -IThirdParty/SDL2/include/SDL2
SDL2L = -LThirdParty/SDL2/lib
SDL2F = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Default target
SDL2WIN: $(BINDIR)win

# Link step
$(BINDIR)win: $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXXC) $(OBJ) $(SDL2L) $(SDL2F) -o $@

# Compile each .cpp into .o in obj/
$(OBJDIR)%.o: $(SRCP)%.cpp
	@mkdir -p $(OBJDIR)
	$(CXXC) -c $< -o $@ -Iinclude/SDL2 $(SDL2I)

# Clean up
clean:
	rm -rf $(OBJDIR) $(BINDIR)

