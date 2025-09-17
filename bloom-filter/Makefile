CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

all:
	$(CXX) $(CXXFLAGS) src/*.cpp -o bloom_filter
	./bloom_filter
	
clean:
	rm bloom_filter