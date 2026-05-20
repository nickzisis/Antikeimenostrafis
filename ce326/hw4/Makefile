CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fsanitize=address

TARGET = hw4
SRCS = HW4.cpp Edge.cpp Vertex.cpp Graph.cpp tinyxml2.cpp
OBJS = $(SRCS:.cpp=.o)
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

HW4.o: HW4.cpp Edges.hpp Vertex.hpp Graph.hpp tinyxml2.h
Edges.o: Edge.cpp Edges.hpp
Vertex.o: Vertex.cpp Vertex.hpp Edges.hpp
Graph.o: Graph.cpp Graph.hpp Vertex.hpp Edges.hpp

clean:
	rm -f $(OBJS) $(TARGET)