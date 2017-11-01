all: stat_testing.c
	gcc stat_testing.c

run: all
	./a.out

clean:
	rm *.o
	rm *~
	rm a.out
