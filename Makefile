#Author: Liam Ryan
#ID: 19769811
#Date Created: 02/10/19
#Last Edited: 20/10/19
#Purpose: the makefile for the TicTacToe program

CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror -std=c89 -g
OBJ =  TicTacToe.o UserInterface.o Settings.o GameManager.o Input.o UCPLinkedList.o Logging.o
EXEC = TicTacToe

#Add SECRET to the CFLAGS and recompile the program
ifdef SECRET
CFLAGS += -D SECRET
EDITOR : clean $(EXEC)
endif

#Add EDITOR to the CFLAGS and recompile the program
ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

TicTacToe.o : TicTacToe.h Settings.h UserInterface.h GameManager.h
	$(CC) -c TicTacToe.c $(CFLAGS)



UserInterface.o : UserInterface.h Settings.h GameManager.h Input.h Logging.h
	$(CC) -c UserInterface.c $(CFLAGS)

Settings.o : Settings.h
	$(CC) -c Settings.c $(CFLAGS)

GameManager.o : GameManager.h Input.h Logging.h
	$(CC) -c GameManager.c $(CFLAGS)

Input.o : Input.h
	$(CC) -c Input.c $(CFLAGS)

Logging.o : Logging.h UCPLinkedList.h
	$(CC) -c Logging.c $(CFLAGS)

UCPLinkedList.o : UCPLinkedList.h
	$(CC) -c UCPLinkedList.c $(CFLAGS)
	
clean :
	rm -f $(OBJ) $(EXEC)
