CC = gcc
BINDIR = bin
SRCDIRS = . ../src
INCDIRS = ../include

DEPFLAGS = -MD -MP
FLAGS = -I$(INCDIRS) $(DEPFLAGS)
CMD_ARGS =  

SRCFILES = $(foreach D, $(SRCDIRS), $(wildcard $(D)/*.c))
# This version keeps objects in src/, matching your current rule
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES))
DEPFILES = $(patsubst %.c, %.d, $(SRCFILES))
BINFILES = $(wildcard $(BINDIR)/*)

# 1. Fixed BINPATH to BINDIR
# 2. Added a command to create the directory
$(BINDIR)/entab.exe: $(OBJFILES)
	@echo "cooking final .exe"
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

# 3. CRITICAL: Include the dependency files so header changes trigger builds
-include $(DEPFILES)


run: 
	$(BINDIR)/out.exe $(CMD_ARGS)

