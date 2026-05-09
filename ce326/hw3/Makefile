CXX = g++
CXXFLAGS = -Wall -Wextra
SANITIZE = -fsanitize=address

TARGET = hw3
SRCS = hw3.cpp Parser.cpp Number.cpp String.cpp ObjectArray.cpp
OBJS = $(SRCS:.cpp=.o)
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SANITIZE)
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
 
hw3.o:         hw3.cpp Parser.hpp
Parser.o:      Parser.cpp Parser.hpp Number.hpp String.hpp ObjectArray.hpp Object.hpp
Number.o:      Number.cpp Number.hpp Object.hpp
String.o:      String.cpp String.hpp Object.hpp Number.hpp ObjectArray.hpp
ObjectArray.o: ObjectArray.cpp ObjectArray.hpp Object.hpp Number.hpp String.hpp
 
clean:
	rm -f $(OBJS) $(TARGET)
 
.PHONY: all clean