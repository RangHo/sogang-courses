CXX = c++
CXXFLAGS = -std=c++14 -I/usr/include/opencv4 -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

all: main

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cpp

clean:
	rm -f main main.o

.PHONY: all clean
