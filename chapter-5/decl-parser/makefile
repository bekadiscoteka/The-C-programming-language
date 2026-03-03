
def = 
OBJFILES = $(patsubst %.c, %.o, $(wildcard ../src/*.c))
FLAGS = -MD -MP -I../include 

bin/parser: parser.o $(OBJFILES)
	gcc $(FLAGS) $^ -o $@ 

%.o: %.c
	gcc -c $(FLAGS) $< -o $@

-include $(patsubst %.o, %.d, $(OBJFILES)) 
