<<<<<<< HEAD
CXXINCFLAGS := -std=c++1z -I /home/maran/eclipse/boost_1_62_0 #-Werror=narrowing #-O3
CXXFLAGS := -Wall -g $(CXXINCFLAGS)
#CXXDEFS := -DDEBUG
LDFLAGS := -lpthread
SRC := $(wildcard *.cpp)
TARGET := $(SRC:%.cpp=bin/%)

all: | bin $(TARGET)

bin/% : %.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEFS) $< -o $@ $(LDFLAGS)

bin:
	mkdir bin

clean:
	rm -fr bin/ *~
=======
CXXFLAGS=-std=c++1z -ggdb
all : main

clean:
	rm -f main *.o
>>>>>>> e5ec62f8ba4232d85c1465295e5c87dfe84b899a
