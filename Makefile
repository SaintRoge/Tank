.PHONY: clean, mrproper, install

.SUFFIXES:

app = Tank
lib = -lsfml-graphics -lsfml-window -lsfml-system
CXX = g++
RM = rm -rf
SRC = "src/"

all: main.o functions.o 
		$(CXX) $^ -o $(app) $(lib)
		@echo "Build finished. You are ready to use $(app) :-)"

%.o: $(SRC)%.cpp
		$(CXX) -c $< -o $@  

clean:
		$(RM) *.o 

mrproper: clean
		$(RM) $(app)  

install: 
		sudo apt-get install libsfml-dev
		make all

run: all
		./$(app)

pro: all clean run

zpro: install clean run

one: all run mrproper