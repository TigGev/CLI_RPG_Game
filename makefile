
CC = g++

CFLAGS = -Wall -Wextra -pedantic -std=c++20

INCLUDES = -I./CLI/headers/characters \
          -I./CLI/headers/gameWorld \
          -I./CLI/headers/inventory \
          -I./CLI/headers/moving \
          -I./CLI/headers/quests \
          -I./CLI/headers/utility

SOURCES = src/Main.cpp \
          src/gameWorld/GameTime.cpp \
          src/gameWorld/GameWorld.cpp \
          src/gameWorld/Location.cpp \
          src/moving/Airship.cpp \
          src/moving/Boat.cpp \
          src/moving/Horse.cpp \
          src/moving/Mount.cpp \
          src/moving/Portal.cpp \
          src/utility/Utility.cpp \
          src/character/Character.cpp \
          src/character/Hero.cpp \
          src/character/Monster.cpp \
          src/character/NPC.cpp \
          src/inventory/Inventory.cpp \
          src/inventory/Item.cpp \
          src/quests/QuestManager.cpp \
          src/quests/Quest.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXEC = CLI_Game

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)

rebuild: clean all

.PHONY: all clean rebuild