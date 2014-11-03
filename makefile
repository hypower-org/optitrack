CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-I ./ -lm
SOURCES=quaternion.C optitrack_driver.C
TESTSOURCES=quaternion.C test.C 
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
	./test 
	rm -f $@
	
