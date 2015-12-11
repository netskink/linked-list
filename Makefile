

TARGET = linked-list
TEST_TARGET = test-list
CC = gcc

# Debug Flags
CFLAGS = -g -Wall
LFLAGS = -g -Wall
LIBS = -lm

# Profile Flags
#CFLAGS = -g -Wall -pg
#LFLAGS = -pg 


.PHONY: default all clean test

# This is so that issuing $ make at the command line
# will build both the demo program and the test program
default: $(TARGET) $(TEST_TARGET)
all: default

# OBJECTS is all .c files renamed as .o
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
# TEST_OBJECTS is all the .o files except for main.o.  
# This is so we don't try to compile a list of object files where we have
# two main routines.
TEST_OBJECTS = $(filter-out main.o, $(OBJECTS))
# TARGET_OBJECTS is the reverse 
TARGET_OBJECTS = $(filter-out test_list.o, $(OBJECTS))
HEADERS = $(wildcard *.h)

# This is so that if any header file changes
# if will cause the c files to be rebuilt into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(TEST_TARGET) $(OBJECTS)

# This is so that if any of the object files used
# to build the test program are modified the test program is rebuilt.
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) -o $@ $(TEST_OBJECTS) $(LFLAGS) $(LIBS) 

# This is so that if any of the object files used
# to build the demo program are modified the demo program is rebuilt.
$(TARGET): $(TARGET_OBJECTS)
	$(CC) -o $@ $(TARGET_OBJECTS) $(LFLAGS) $(LIBS) 

clean:
	-rm -f *.o
	-rm -f $(TARGET) $(TEST_TARGET)

test: default
	echo Running  $(TEST_TARGET)
	./$(TEST_TARGET) 












