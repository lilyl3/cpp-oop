CXX = g++
FLAGS = -std=c++17 -Wall -I./include

SRCS = main.cpp source/gps.cpp source/sensor.cpp source/radar.cpp
TARGET = main

all:
	$(CXX) $(FLAGS) $(SRCS) -o $(TARGET)

clean:
	rm $(TARGET)
