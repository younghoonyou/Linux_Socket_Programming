CC = g++#compiler

CXXFLAGS = -Wall -02#compile option for C++ Wall(complie warning) 02(optimize level 2)

OBJS = server.o

TARGET = server.out

$(TARGET) = $(OBJS)
	$(CC) -o $@ $(OBJS)

server.o : server.cpp
	$(CC) $(CXXFLAGS) -c server.cpp

clean:
	rm -rf $(OBJS) test
