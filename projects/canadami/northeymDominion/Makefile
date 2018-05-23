CFLAGS = -Wall -fpic -coverage -lm

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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean: removeunittestresults.out removecardtestresults.out
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe 

removecardtestresults.out:
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer

removeunittestresults.out: 
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

unit1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unit2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unit3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unit4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

card1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

card2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

card3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

card4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)


unittestresults.out: unit1 unit2 unit3 unit4 card1 card2 card3 card4 
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	gcov unittest1.c -b >> unittestresults.out	
	gcov unittest2.c -b >> unittestresults.out	
	gcov unittest3.c -b >> unittestresults.out	
	gcov unittest4.c -b >> unittestresults.out	
	gcov cardtest1.c -b >> unittestresults.out
	gcov cardtest2.c -b >> unittestresults.out	
	gcov cardtest3.c -b >> unittestresults.out	
	gcov cardtest4.c -b >> unittestresults.out	

random1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

random2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

random3: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestresults.out: random1 random2 random3
	./randomtestcard1 &> randomtestcard1.out
	./randomtestcard2 >> randomtestcard2.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	gcov dominion.c -b >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	gcov randomcardtest1.c -b >> randomtestcard1.out	
	gcov randomcardtest2.c -b >> randomtestcard2.out	
	gcov randomtestadventurer.c -b >> randomtestadventurer.out	


