CC=g++
MASTER_CFILE = master.cpp
CHILD_CFILE =

MASTER_OBJ=$(MASTER_CFILE:.cpp=.o)
CHILD_OBJ=$(CHILD_CFILE:.cpp=.o)

MASTER_EXE = master
CHILD_EXE = child

CFLAGS = -g -Wall
MATH = -lm

HEADER_FILE = helper.h

SRC =
SHARE_OBJ = linked_list.o tree.o build_tree.o
SHARE_HEAD = linked_list.h tree.h build_tree.h

%.o: %.cpp $(SHARE_HEAD)
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

all: $(MASTER_EXE)

$(MASTER_EXE): $(MASTER_OBJ) $(SHARE_OBJ)
	$(CC) -std=c++11 -o $(MASTER_EXE) $^ $(CFLAGS)

clean:
	rm $(MASTER_EXE) $(MASTER_OBJ) $(SHARE_OBJ)
