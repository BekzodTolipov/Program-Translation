CC=g++
MASTER_CFILE = master.cpp
CHILD_CFILE =

MASTER_OBJ=$(MASTER_CFILE:.cpp=.o)
CHILD_OBJ=$(CHILD_CFILE:.cpp=.o)

MASTER_EXE = p0
CHILD_EXE = child

CFLAGS = -g -Wall
MATH = -lm

HEADER_FILE = helper.h

CPP_11 = -std=c++11

SRC =
SHARE_OBJ = build_tree.o
SHARE_HEAD = build_tree.h

%.o: %.cpp $(SHARE_HEAD)
	$(CC) $(CPP_11) -c -o $@ $< $(CFLAGS)

all: $(MASTER_EXE)

$(MASTER_EXE): $(MASTER_OBJ) $(SHARE_OBJ)
	$(CC) $(CPP_11) -o $(MASTER_EXE) $^ $(CFLAGS)

clean:
	rm $(MASTER_EXE) $(MASTER_OBJ) $(SHARE_OBJ)
