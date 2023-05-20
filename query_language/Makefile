TARGET = kod
SRCS = \
	   scaner.cpp \
	   parcer.cpp \
	   interpreter.cpp \
	   classes.cpp \
	   main.cpp

OBJS = $(SRCS:.cpp=.o)
CC = g++-10

.PHONY: all clean memcheck

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -std=c++20 -g -o $(TARGET) $(OBJS) -lm

%.o: %.cpp
	$(CC) -std=c++20 -c $< -o $@

memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)