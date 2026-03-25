

SRCDIRS = . ../src 
FLAGS = -MD -MP -I../include -g
SRCFILES = $(foreach D, $(SRCDIRS), $(wildcard $(D)/*.c))
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES))
DFILES = $(patsubst %.c, %.d, $(SRCFILES))

bin/dh: $(OBJFILES) 
	gcc $(FLAGS) $^ -o $@ 


%.o: %.c 
	gcc $(FLAGS) -c $< -o $@

-include $(DFILES)
