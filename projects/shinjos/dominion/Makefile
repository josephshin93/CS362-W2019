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

unittest2: unittest2.c dominion.o rngs.o domtest_helpers.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o domtest_helpers.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o domtest_helpers.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o domtest_helpers.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o domtest_helpers.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o domtest_helpers.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o domtest_helpers.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o domtest_helpers.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Running All Unit Tests..." > unittestresults.out
	echo "\n\nRunning unit test 1:" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\n\nRunning unit test 2:" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\n\nRunning unit test 3:" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\n\nRunning unit test 4:" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\n\nRunning card test 1:" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\n\nRunning card test 2:" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\n\nRunning card test 3:" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	echo "\n\nRunning card test 4:" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out


# random testing
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o domtest_helpers.o
	gcc randomtestadventurer.c -o randomtestadventurer -g dominion.o rngs.o domtest_helpers.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o domtest_helpers.o
	gcc randomtestcard1.c -o randomtestcard1 -g dominion.o rngs.o domtest_helpers.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o domtest_helpers.o
	gcc randomtestcard2.c -o randomtestcard2 -g dominion.o rngs.o domtest_helpers.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	echo "Adventurer Card Random Test:\n" > randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	echo >> randomtestadventurer.out
	echo >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1
	echo "Card 1 Random Test:\n" > randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	echo >> randomtestcard1.out
	echo >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	echo "Card 2 Random Test:\n" > randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	echo >> randomtestcard2.out
	echo >> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out

randomtests:
	make clean
	make randomtestadventurer.out
	cp dominion.c.gcov testing_snapshots/adventurerrandtest.txt
	make clean
	make randomtestcard1.out
	cp dominion.c.gcov testing_snapshots/minionrandtest.txt
	make clean
	make randomtestcard2.out
	cp dominion.c.gcov testing_snapshots/smithyrandtest.txt




player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestadventurer randomtestcard1 randomtestcard2
