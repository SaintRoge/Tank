.PHONY: clean, mrproper, install

.SUFFIXES:

app = Tank
lib = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXX = g++
RM = rm -rf
SRC = src/bin/
FLAGS = -std=c++11
ROOTMESSAGE = "ACHTUNG ! You must be root to do it !"

all: main.o functions.o tank.o bullet.o enemies.o game.o
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

install: all clean
		@echo $(ROOTMESSAGE)
		cp -r ../Tank /opt/
		ln -s /opt/Tank/Tank /usr/bin/
		cp Tank.desktop /usr/share/applications/
		@echo "Done !"

run: all
		@echo "Trying to start $(app)..."
		./$(app)

remove:
		@echo $(ROOTMESSAGE)
		$(RM) /usr/bin/Tank /usr/share/applications/Tank.desktop
		@echo "Done !"

reinstall: remove install


pro: all clean run

zpro: install clean run

one: all run mrproper
