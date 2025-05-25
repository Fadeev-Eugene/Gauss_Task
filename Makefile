CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/include/eigen3 -O3 -Wall -Wextra
TEST_CXXFLAGS = $(CXXFLAGS) -g
LDFLAGS = 
TEST_LDLIBS = -lgtest -lgtest_main -pthread

MAIN_SRC = funcs.cpp main.cpp
TEST_SRC = funcs.cpp tests.cpp

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

TARGET = gauss_solver
TEST_TARGET = gauss_tests

.PHONY: all test clean

all: $(TARGET)

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

$(TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(TEST_CXXFLAGS) $^ -o $@ $(LDFLAGS) $(TEST_LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o *.csv
