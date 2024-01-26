CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = Sokoban.hpp
# Your compiled .o files
OBJECTS = Sokoban.o
# The name of your program
PROGRAM = Sokoban
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(TEST) Sokoban.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

Sokoban.a: $(OBJECTS)
	ar rcs Sokoban.a $(OBJECTS)

clean:
	rm *.o $(PROGRAM) $(TEST) Sokoban.a

lint:
	cpplint *.cpp *.hpp
