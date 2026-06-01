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

out: out1 out2 out3 out4 out5 out6 out7

out1:
	./hw4 < test1a.in > test1a.out
	diff -urN test1a.out test1a.std
	./hw4 < test1b.in > test1b.out
	diff -urN test1b.out test1b.std
	./hw4 < test1c.in > test1c.out
	diff -urN test1c.out test1c.std
	
out2:	
	./hw4 < test2a.in > test2a.out
	diff -urN test2a.out test2a.std
	./hw4 < test2b.in > test2b.out
	diff -urN test2b.out test2b.std
	
out3:	
	./hw4 < test3a.in > test3a.out
	diff -urN test3a.out test3a.std
	./hw4 < test3b.in > test3b.out
	diff -urN test3b.out test3b.std
	
out4:	
	./hw4 < test4a.in > test4a.out
	diff -urN test4a.out test4a.std
	./hw4 < test4b.in > test4b.out
	diff -urN test4b.out test4b.std
	
out5:	
	./hw4 < test5a.in > test5a.out
	diff -urN test5a.out test5a.std
	./hw4 < test5b.in > test5b.out
	diff -urN test5b.out test5b.std
	./hw4 < test5c.in > test5c.out
	diff -urN test5c.out test5c.std
	
# diff1:
#	./hw4 < test1a.in > test1a.std
#	./hw4 < test1b.in > test1b.std
#	./hw4 < test1c.in > test1c.std
#	./hw4 < test2a.in > test2a.std
#	./hw4 < test2b.in > test2b.std
#	./hw4 < test3a.in > test3a.std
#	./hw4 < test3b.in > test3b.std
#	./hw4 < test4a.in > test4a.std
#	./hw4 < test4b.in > test4b.std
#	./hw4 < test5a.in > test5a.std
#	./hw4 < test5b.in > test5b.std
#	./hw4 < test5c.in > test5c.std

clean:
	rm *.out