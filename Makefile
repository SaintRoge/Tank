.PHONY: clean, mrproper, install

.SUFFIXES:

app = Tank
lib = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXX = g++
RM = rm -rf
SRC = src/bin/
FLAGS = -std=c++11

all: main.o functions.o tank.o bullet.o
		$(CXX) $(FLAGS) $^ -o $(app) $(lib)
		@echo "Finished building: $^"
		@echo "Build finished. You are ready to use $(app) :-)"

%.o: $(SRC)%.cpp
		$(CXX) $(FLAGS) -c $< -o $@
		@echo "Finished building: $^"   

clean:
		$(RM) *.o 
		@echo "All project useless files/folders have been deleted"

mrproper: clean
		$(RM) $(app)
		@echo "All project files/folders have been deleted"  

install: 
		sudo apt-get install libsfml-dev build-essential
		@echo "The SFML lib and the c++ builder have been installed"
		make all

run: all
		@echo "Trying to start $(app)..."
		./$(app)

pro: all clean run

zpro: install clean run

one: all run mrproper