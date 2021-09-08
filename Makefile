
SRC = src
INC = include
OBJ = obj
LIB = lib

CC = gcc


all:$(OBJ)/matrixmul_pthread.o

$(OBJ)/matrixmul_pthread.o:$(SRC)/matrixmul_pthread.C
	$(CC) -o $(OBJ)/matrixmul_pthread.o $(SRC)/matrixmul_pthread.c 

run:$(OBJ)/matrixmul_pthread.o
	.\$(OBJ)/matrixmul_pthread.o 10 100

clean: 
	rm -f $(OBJ)/matrixmul_pthread.o