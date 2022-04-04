CC = g++#compiler

CXXFLAGS = -Wall#compile option for C++ Wall(complie warning) 02(optimize level 2)

OBJS1 = server.cpp
OBJS2 = client.cpp

all : server client

server : $(OBJS1)
	$(CC) -o server $(OBJS1) -lpthread

client : $(OBJS2)
	$(CC) -o client $(OBJS2) -lpthread

#server.o : server.cpp
#	$(CC) $(CXXFLAGS) -c server.cpp

#client.o : client.cpp
#	$(CC) $(CXXFLAGS) -c client.cpp

clean:
	rm *o $(all)
