testme: testme.c
	gcc -Wall -fpic -coverage -std=c99 testme.c -o testme

runquiz: testme
	./testme
	gcov -b testme.c

clean:
	rm -f testme *.gcda *.gcno
