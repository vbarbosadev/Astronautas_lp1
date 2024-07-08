CXX = g++

CXXFLAGS = -std=c++11 -Wall

TARGET = prog

SRCS = main.cpp sistema.cpp voo.cpp astronauta.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)