TARGET = kod 


SRCS = \
	   scaner.cpp \
	   parcer.cpp \
	   interpreter.cpp \
	   classes.cpp \
		main.cpp
	   

CC = g++-10

.PHONY: all clean memcheck

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -std=c++20 $(addprefix -I,$(HDRS)) -g -o $(TARGET)  $(SRCS) -lm

memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) 

clean:
	rm -f $(TARGET) 