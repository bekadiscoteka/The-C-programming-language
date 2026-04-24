bin/out: main.o sMalloc.o
	gcc $^ -o $@

%.o: %.c
	gcc $^ -o $@ -c

clean:
	rm *.o
