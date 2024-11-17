CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

cube: cube.o matrixMul.o screen.o
	$(CXX) $(CFLAGS) $^ -o $@

cube.o: cube.cpp matrixMul.hpp helpers.hpp screen.hpp
	$(CXX) $(CFLAGS)  -g -c $< -o $@

matrixMul.o: matrixMul.cpp matrixMul.hpp helpers.hpp 
	$(CXX) $(CFLAGS) -g -c $< -o $@

screen.o: screen.cpp screen.hpp
	$(CXX) $(CFLAGS) -g -c $< -o $@


clean: 
	rm -r *.o cube

.PHONY:
	.clean
