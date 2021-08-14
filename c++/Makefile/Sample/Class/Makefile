# /home/dir_a/Makefile

OBJS = Sample.o
TARGET = run1.x
TARGETS = $(TARGET)

include ../Makefile.in

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

# サフィックスルール
.c.cpp.o:
	$(CC) $(CFLAGS) -c $<

#Sample.o : Sample.cpp Sample.hpp

