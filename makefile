all: stat_testing.c
	gcc stat_testing.c

run: all
	./a.out

clean:
	rm a.out
	rm test_file
