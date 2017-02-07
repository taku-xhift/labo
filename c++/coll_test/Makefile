# sample Makefile

CC = g++
OPT = -Wall -g
LIBS = -L../lib -L/usr/X11R6/lib -L/usr/lib -L/usr/local/lib \
       -lm -lGL -lGLU -lode -ldrawstuff
INCS = -I. -I../include -I/usr/X11R6/include

TARGET = $(SRC:%.cpp=%)
OBJ = $(SRC:%.cpp=%.o)
SRC = ground.cpp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OPT) $(OBJ) $(LIBS) $(INCS) -o $@

$(OBJ): $(SRC)
	$(CC) $(OPT) $(INCS) -c $(SRC)

clean:
	rm -f *.o $(TARGET)

