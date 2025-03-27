
CC = g++

CFLAGS = -Wall -Wextra -pedantic -std=c++17 -g

INCLUDES = -I./CLI/headers/characters \
          -I./CLI/headers/gameWorld \
          -I./CLI/headers/inventory \
          -I./CLI/headers/moving \
          -I./CLI/headers/quests \
          -I./CLI/headers/utility

MAIN_SOURCES = src/Main.cpp \
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

TEST_SOURCES = tests/gameTime_test.cpp \
               tests/hero_test.cpp \
               tests/monster_test.cpp \
               tests/gameWorld_test.cpp \
               tests/location_test.cpp \
               tests/npc_test.cpp

MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)

COMMON_OBJECTS = $(filter-out src/Main.o, $(MAIN_OBJECTS))

TEST_EXES = $(TEST_SOURCES:.cpp=)

EXEC = CLI_Game

GTEST_LIBS = -lgtest -lgtest_main -pthread  # Укажите правильные библиотеки, если нужно

all: $(EXEC)

$(EXEC): $(MAIN_OBJECTS)
	$(CC) $(MAIN_OBJECTS) -o $(EXEC)

tests: $(TEST_EXES)

tests/gameTime_test: tests/gameTime_test.o $(COMMON_OBJECTS)
	$(CC) tests/gameTime_test.o $(COMMON_OBJECTS) $(GTEST_LIBS) -o $@
tests/hero_test: tests/hero_test.o $(COMMON_OBJECTS)
	$(CC) tests/hero_test.o $(COMMON_OBJECTS) $(GTEST_LIBS) -o $@
tests/monster_test: tests/monster_test.o $(COMMON_OBJECTS)
	$(CC) tests/monster_test.o $(COMMON_OBJECTS) $(GTEST_LIBS) -o $@
tests/gameWorld_test: tests/gameWorld_test.o $(COMMON_OBJECTS)
	$(CC) tests/gameWorld_test.o $(COMMON_OBJECTS) $(GTEST_LIBS) -o $@
tests/location_test: tests/location_test.o $(COMMON_OBJECTS)
	$(CC) tests/location_test.o $(COMMON_OBJECTS) $(GTEST_LIBS) -o $@
tests/npc_test: tests/npc_test.o $(COMMON_OBJECTS)
	$(CC) tests/npc_test.o $(COMMON_OBJECTS) $(GTEST_LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(MAIN_OBJECTS) $(TEST_EXES) $(EXEC) $(TEST_EXES:=.o)

rebuild: clean all

run-gameTime: tests/gameTime_test
	./tests/gameTime_test
run-hero: tests/hero_test
	./tests/hero_test
run-monster: tests/monster_test
	./tests/monster_test
run-gameWorld: tests/gameWorld_test
	./tests/gameWorld_test
run-location: tests/location_test
	./tests/location_test
run-npc: tests/npc_test
	./tests/npc_test

.PHONY: all clean rebuild tests run-gameTime run-hero run-monster run-gameWorld run-location run-npc