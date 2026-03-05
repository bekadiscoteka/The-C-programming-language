
SRCDIRS = ../src .
SRCFILES = $(foreach D, $(SRCDIRS), $(wildcard $(D)/*.c))
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES));
FLAGS = -MD -MP -I../include
bin/wc: $(OBJFILES) 
	gcc $(FLAGS) $^ -o $@ 

%.o: %.c
	gcc -c $(FLAGS) $< -o $@


-include $(DFILES)
