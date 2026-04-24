bin/out: main.o sMalloc.o
	gcc $^ -o $@ -g

%.o: %.c
	gcc $^ -o $@ -c

clean:
	rm *.o
