CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -g -Werror -Wall -Wextra

EXECUTABLE_NAME = prog.out
SOURCES = main.cpp rbt.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(LFLAGS) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUABLE_NAME)
