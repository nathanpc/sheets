CXX = clang++
CXXFLAGS = -Wall
LDFLAGS = -pthread -lboost_filesystem -lboost_system
OBJ = src/main.o src/dir_parse.o
PREFIX = /usr/local

all: sheets

sheets: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

debug: CXXFLAGS += -g3 -DDEBUG
debug: all

%.o: %.c
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $<

clean:
	rm -rf src/*.o src/core
	rm -f sheets
