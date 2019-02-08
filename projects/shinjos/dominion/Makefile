CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


# unit testing and card testing
# make sure these are correct
domtest_helpers.o: domtest_helpers.h domtest_helpers.c dominion.h
	gcc -c domtest_helpers.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o domtest_helpers.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Running unit test 1:" > unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "Running unit test 2:" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "Running unit test 3:" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "Running unit test 4:" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "Running card test 1:" > unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "Running card test 2:" > unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "Running card test 3:" > unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "Running card test 4:" > unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out



player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
