CXX=g++
CXXFLAGS= -Wall -pedantic -g -std=c++11
EXEC=robot

all: $(EXEC)

robot: main.o graph.o
	$(CXX) -o $@ $^ 

main.o: graph.h

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf $(EXEC)
