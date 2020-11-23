CXX=g++-10
FLAGS= -Wall -lncurses
FILES=Board.cc Rule.cc controller.cc
OBJFILES=Board.o Rule.o controller.o
TARGET=game-of-life

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJFILES)



clean:
	rm -f $(OBJFILES) $(TARGET)
