#Makefile

# Macros
TARGET = Hello

SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)
HEADS = $(shell ls *.hpp)

CXXFLAGS = -o2 -g -Wall
CXXOPTIONS = -lstdc++


$(TARGET): $(OBJS) $(HEADS)
	@echo $^
	$(CXX) -o $(TARGET) $(CXXFLAGS) $(OBJS) $(LIBS) $(CSSOPTIONS)

all: subsystem $(TARGET)
	@echo "all"

run: all
	@echo "run"
	./$(TARGET)

depend:
	@echo "depend"
	$(CXX) -MM -MG $(SRCS) > Makefile.depend

clean:
	@echo "clean"
	rm -f $(OBJS) $(TARGET) *~ \#*\#

subsystem:
	@echo "subsystem"
	$(MAKE) -C subdir

-include Makefile.depend


