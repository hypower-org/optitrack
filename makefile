CC=g++
CFLAGS=-c -Wall
LDFLAGS=-I ./ -lm -L ./vrpn/pc_linux64 -lvrpn -lvrpnserver -lpthread
SOURCES=$(wildcard src/*.C)
TESTSOURCES=./src/quaternion.C $(wildcard tests/*.C)
OBJECTS=$(SOURCES:.cpp=.o) 
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
EXECUTABLE=od

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ 

.PHONY: clean

clean: 
	rm -f $(EXECUTABLE)

test: $(TESTOBJECTS)
	$(CC) $(TESTOBJECTS) $(LDFLAGS) -o $@
	./$@
	rm -f $@
	
