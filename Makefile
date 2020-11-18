CXX=g++-10
FLAGS= -Wall
FILES=Board.cc Rule.cc main.cc
OBJFILES=Board.o Rule.o main.o
TARGET=conways-gol

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJFILES)



clean:
	rm -f $(OBJFILES) $(TARGET)
