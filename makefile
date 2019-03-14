# change application name here (executable output name)
TARGET = dictionary
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
 
OBJS=    main.o
LCT = /home/anhtu/C\ advance/C_project/src/control.c
LBT = /home/anhtu/C\ advance/C_project/src/bt/libbt.a
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LCT) $(LBT) $(LDFLAGS)
    
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o   
    
clean:
	rm -f *.o $(TARGET)

