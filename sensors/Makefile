CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l5

l5: main.o SensorCollection.o
	${CXX} ${LDFLAGS} $^ -o $@

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

SensorCollection.o: SensorCollection.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f *.o l5
