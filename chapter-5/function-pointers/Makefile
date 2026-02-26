PROG = qsort.exe
param = 
CC = gcc
BINDIR = bin
SRCDIRS = . src ../src
INCDIRS = . include ../include
DFLAGS = -MD -MP
SRCFILES = $(foreach D, $(SRCDIRS), $(wildcard $(D)/*.c))
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES))
DFILES = $(patsubst %.c, %.d, $(SRCFILES))
INCFLAGS = $(foreach D, $(INCDIRS), -I$(D))
FLAGS = $(DFLAGS) $(INCFLAGS) 

$(BINDIR)/$(PROG): $(OBJFILES) 
	$(CC) $(FLAGS) $^ -o $@ -g

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

-include $(DFILES)

run: 
	$(BINDIR)/$(PROG) $(foreach D, $(param), -$(D)) 

