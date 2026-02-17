CC = gcc
MAINOBJ = entab.o
OBJLIST = $(MAINOBJ) mystd.o date.o mystring.o
OUT = entab.exe
FLAGS = -DPTR_VERSION 

$(OUT): $(OBJLIST)
	$(CC) $^ -o $@

%.o: %.c 
	$(CC) -c $(FLAGS) $^  -o $@  

mainonly: # compile only main
	$(CC) -c $(FLAGS) main.c -o main.o
	$(CC) $(OBJLIST) -o $(OUT) 

run:
	./$(OUT) 

clean: 
	del $(OBJLIST)

