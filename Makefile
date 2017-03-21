# set paths
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# lists of files
INC = $(wildcard $(INC_DIR)/*.h)
SRC = $(wildcard $(SRC_DIR)/*.cxx)
OBJ = $(SRC:$(SRC_DIR)/%.cxx=$(OBJ_DIR)/%.o)

# compiler options
CXX = g++
CXXFLAGS = -I $(INC_DIR) -lsfml-graphics -lsfml-window -lsfml-system

# binary files
BIN = $(BIN_DIR)/hello_world $(BIN_DIR)/hello_electron

# dependencies
$(BIN_DIR)/hello_world.dep = hello_world.o
$(BIN_DIR)/hello_electron.dep = hello_electron.o

# makes
all: init $(OBJ) $(BIN)

# compiling
$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	@tabs 10
	@echo -ne 'Compiling \033[1m$@\033[0m...'
	@$(CXX) -c $< -o $@  $(CXXFLAGS)
	@echo -e '\tdone'

# linking
$(BIN):
	@tabs 10
	@echo -ne 'Linking \033[1m$@\033[0m...'
	@$(CXX) $(addprefix $(OBJ_DIR)/, $($@.dep)) -o $@ $(CXXFLAGS) 
	@echo -e '\tdone'

# initialize output folders
init:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	
# remove binaries
clean:
	@echo -ne 'Removing \033[1m$(OBJ) $(BIN)\033[0m...'
	@rm -f $(OBJ) $(BIN)
	@echo ' done'