
CPP=g++
CPPFLAGS=-O0 -g3 -Wall
INCLUDES=-I./dep/MJPA-SimpleJSON/src/ -I./src/
OBJECTS=./dep/MJPA-SimpleJSON/src/JSON.o ./dep/MJPA-SimpleJSON/src/JSONValue.o \
	./src/perftest_main.o ./src/perftest_runner.o
LIB=./lib/perftest.a


%.o: %.cpp
	@echo " [C++] Compiling $<"
	@$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

all: $(OBJECTS)
	@ar rs $(LIB) $(OBJECTS) 2> /dev/null

test: all
	@$(CPP) $(INCLUDES) $(CPPFLAGS) -o tests/SimpleTest tests/SimpleTest.cpp $(LIB)

clean:
	@echo " [CLN] Cleaning object files"
	@rm -f $(OBJECTS)
	@echo " [CLN] Removing static library"
	@rm -f $(LIB)
	@echo " [CLN] Removing tests"
	@rm -f tests/SimpleTest
