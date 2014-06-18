TARGET=$(shell basename `pwd`)
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)

CC=g++

CPPFLAGS+=-O2 -std=c++0x -L/usr/include
LDFLAGS+=-O2 -std=c++0x -L/usr/include

CPPFLAGS+=$(shell pkg-config --cflags sqlite3)
LDFLAGS+=$(shell pkg-config --libs sqlite3)

all: $(TARGET)

$(OBJECTS): $(SOURCES)

$(TARGET): $(OBJECTS)
		$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LOADLIBES) $(LDLIBS)

clean:
		$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
