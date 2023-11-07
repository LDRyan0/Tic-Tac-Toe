#Author: Liam Ryan
#ID: 19769811
#Date Created: 02/10/19
#Last Edited: 20/10/19
#Purpose: the makefile for the TicTacToe program

CC      = gcc
CFLAGS  = -ansi -pedantic -Wall -Werror -g
EXEC    = TicTacToe

LOG_DIR = logs
SRC_DIR = src
OBJ_DIR = obj
OBJ     = $(addprefix $(OBJ_DIR)/, TicTacToe.o UserInterface.o Settings.o GameManager.o \
          Input.o LinkedList.o Logging.o )
vpath %.c $(SRC_DIR)
vpath %.h $(SRC_DIR)

#Add SECRET to the CFLAGS and recompile the program
ifdef SECRET
CFLAGS += -D SECRET
EDITOR : 
	rm $(EXEC)
endif

#Add EDITOR to the CFLAGS and recompile the program
#ifdef EDITOR
CFLAGS += -D EDITOR
#endif

all : dirs $(EXEC)

dirs : 
	@[ -d $(LOG_DIR) ] || mkdir $(LOG_DIR)
	@[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

	
clean :
	rm $(OBJ)
	rm $(EXEC)
