CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra \
           -Iinclude \
           -I/opt/homebrew/include    # <- include path for gtest

# Linker flags
LDFLAGS = -L/opt/homebrew/lib \
          -lgtest -lgtest_main -pthread  # <- link against gtest

# Test source files
TEST_SRC = $(wildcard test/*.cpp)

TARGET = cache

all:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(LDFLAGS) -o $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
