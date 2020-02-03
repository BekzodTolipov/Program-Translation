CC=gpp
MASTER_CFILE = master.cpp
CHILD_CFILE =

MASTER_OBJ=$(MASTER_CFILE:.c=.o)
CHILD_OBJ=$(CHILD_CFILE:.c=.o)

MASTER_EXE = master
CHILD_EXE = child

CFLAGS = -g -Wall
MATH = -lm

HEADER_FILE = helper.h

SRC =
SHARE_OBJ = list.o
SHARE_HEAD = list.h

%.o: %.c $(SHARE_HEAD)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(MASTER_EXE)

$(MASTER_EXE): $(MASTER_OBJ) $(SHARE_OBJ)
	$(CC) -o $(MASTER_EXE) $^ $(CFLAGS)
	
$(CHILD_EXE): $(CHILD_OBJ) $(SHARE_OBJ)
	$(CC) -o $(CHILD_EXE) $^ $(CFLAGS)

clean:
	rm $(MASTER_EXE) $(MASTER_OBJ) $(CHILD_OBJ) $(SHARE_OBJ)
