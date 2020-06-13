MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

CXXFLAGS=-O0 -g -Wall -MMD -Wno-unused-function -std=c++17
CXXFLAGS+=-Iinclude
CFLAGS=$(CXXFLAGS)
CC=gcc
CXX=g++

LDLIBS= -Llib -lglfw -lGL -ldl
SRC=$(wildcard src/*.cpp)
SRC_C=
OBJS=$(patsubst %.cpp, %.o, $(SRC)) $(patsubst %.c, %.o, $(SRC_C))
DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: bin/exe

-include $(DEPS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

bin/exe: $(OBJS) 
	mkdir -p bin
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f $(DEPS) $(OBJS) gmon.out perf bin/exe

gmon: 
	gprof bin/exe gmon.out > perf

threading:
	make -j

run: bin/exe
	./bin/exe