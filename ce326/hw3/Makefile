CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
 
TARGET = hw3
SRCS = hw3.cpp Parser.cpp Number.cpp String.cpp ObjectArray.cpp
OBJS = $(SRCS:.cpp=.o)
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
hw3.o:         hw3.cpp Parser.hpp
Parser.o:      Parser.cpp Parser.hpp Number.hpp String.hpp ObjectArray.hpp Object.hpp
Number.o:      Number.cpp Number.hpp Object.hpp
String.o:      String.cpp String.hpp Object.hpp Number.hpp ObjectArray.hpp
ObjectArray.o: ObjectArray.cpp ObjectArray.hpp Object.hpp Number.hpp String.hpp
 
clean:
	rm -f $(OBJS) $(TARGET)
 
# ── Tests ─────────────────────────────────────────────────
EXEC = ./hw3
 
out: out1 out2 out3 out4 out5 out6 out7
 
out1:
	$(EXEC) < t1.1.in > t1.1.out
	diff -urN t1.1.std t1.1.out
	$(EXEC) < t1.2.in > t1.2.out
	diff -urN t1.2.std t1.2.out
	$(EXEC) < t1.3.in > t1.3.out
	diff -urN t1.3.std t1.3.out
	$(EXEC) < t1.4.in > t1.4.out
	diff -urN t1.4.std t1.4.out
	$(EXEC) < t1.5.in > t1.5.out
	diff -urN t1.5.std t1.5.out
	$(EXEC) < t1.6.in > t1.6.out
	diff -urN t1.6.std t1.6.out
	$(EXEC) < t1.7.in > t1.7.out
	diff -urN t1.7.std t1.7.out
	$(EXEC) < t1.8.in > t1.8.out
	diff -urN t1.8.std t1.8.out
	$(EXEC) < t1.9.in > t1.9.out
	diff -urN t1.9.std t1.9.out
	$(EXEC) < t1.10.in > t1.10.out
	diff -urN t1.10.std t1.10.out
 
out2:
	$(EXEC) < t2.1.in > t2.1.out
	diff -urN t2.1.std t2.1.out
	$(EXEC) < t2.2.in > t2.2.out
	diff -urN t2.2.std t2.2.out
 
out3:
	$(EXEC) < t3.1.in > t3.1.out
	diff -urN t3.1.std t3.1.out
	$(EXEC) < t3.2.in > t3.2.out
	diff -urN t3.2.std t3.2.out
	$(EXEC) < t3.3.in > t3.3.out
	diff -urN t3.3.std t3.3.out
 
out4:
	$(EXEC) < t4.1.in > t4.1.out
	diff -urN t4.1.std t4.1.out
	$(EXEC) < t4.2.in > t4.2.out
	diff -urN t4.2.std t4.2.out
	$(EXEC) < t4.3.in > t4.3.out
	diff -urN t4.3.std t4.3.out
	$(EXEC) < t4.4.in > t4.4.out
	diff -urN t4.4.std t4.4.out
 
out5:
	$(EXEC) < t5.1.in > t5.1.out
	diff -urN t5.1.std t5.1.out
	$(EXEC) < t5.2.in > t5.2.out
	diff -urN t5.2.std t5.2.out
	$(EXEC) < t5.3.in > t5.3.out
 
out6:
	$(EXEC) < t6.1.in > t6.1.out
	diff -urN t6.1.std t6.1.out
	$(EXEC) < t6.2.in > t6.2.out
	diff -urN t6.2.std t6.2.out
	$(EXEC) < t6.3.in > t6.3.out
	diff -urN t6.3.std t6.3.out
	$(EXEC) < t6.4.in > t6.4.out
	diff -urN t6.4.std t6.4.out
	$(EXEC) < t6.5.in > t6.5.out
	diff -urN t6.5.std t6.5.out
 
out7:
	$(EXEC) < t7.1.in > t7.1.out
	diff -urN t7.1.std t7.1.out
	$(EXEC) < t7.2.in > t7.2.out
	diff -urN t7.2.std t7.2.out
	$(EXEC) < t7.3.in > t7.3.out
	diff -urN t7.3.std t7.3.out
	$(EXEC) < t7.4.in > t7.4.out
	diff -urN t7.4.std t7.4.out
	$(EXEC) < t7.5.in > t7.5.out
	diff -urN t7.5.std t7.5.out
 
cleanout:
	rm *.out
 
.PHONY: all clean out out1 out2 out3 out4 out5 out6 out7 cleanout