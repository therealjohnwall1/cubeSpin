CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

cube: cube.o matrixMul.o 
	$(CXX) $(CFLAGS) $^ -o $@

cube.o: cube.cpp matrixMul.hpp helpers.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

matrixMul.o: matrixMul.cpp matrixMul.hpp helpers.hpp
	$(CXX) $(CFLAGS) -c $< -o $@


clean: rm -f *.o cube

.PHONY:
	.clean
