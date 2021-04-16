CC = g++
CFLAGS = -Wall -c
LFLAGS = -lpthread -lrt
TARGET = mizzo

all: $(TARGET)

$(TARGET): main.o Parse.o CandyFactory.o producer.o consumer.o io.o
	$(CC) main.o Parse.o CandyFactory.o producer.o consumer.o io.o -o $(TARGET) $(LFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Parse.o: Parse.cpp parse.h
	$(CC) $(CFLAGS) Parse.cpp

CandyFactory.o: CandyFactory.cpp CandyFactory.h
	$(CC) $(CFLAGS) CandyFactory.cpp

producer.o: producer.cpp producer.h
	$(CC) $(CFLAGS) producer.cpp

consumer.o: consumer.cpp consumer.h
	$(CC) $(CFLAGS) consumer.cpp

io.o: io.cpp io.h
	$(CC) $(CFLAGS) io.cpp

clean:
	rm -f core *.o $(TARGET)