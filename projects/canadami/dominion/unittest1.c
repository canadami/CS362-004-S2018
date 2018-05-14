#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "fullDeckCount"

//assert two values are equal
int myAssert(int left, int right)
{
	if(left != right)
		return 1;
	
	return 0;
}

int main()
{
	int i;
	int test;
	int seed = 13;
	int numPlayers = 2;
	int thisPlayer = 0;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 
	struct gameState G, testG;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, cards, seed, &G);
	//copy gamestate to testG
	memcpy(&testG, &G, sizeof(struct gameState));	
	
	printf("----------------- Testing Card: %s ----------------\n", TESTFUNCTION);
	printf("\n");


	//initialize size of the three arrays
	testG.deckCount[thisPlayer] = 50;
	testG.handCount[thisPlayer] = 50;
	testG.discardCount[thisPlayer] = 50;

void fillArray()
{
	//fill arrays with -99 values
	for(i = 0; i < 50; i++)
	{
		testG.deck[thisPlayer][i] = -99;
		testG.hand[thisPlayer][i] = -99;
		testG.discard[thisPlayer][i] = -99;		
	}
}

	int card1 = 1;
	int card2 = 10;
	int card3 = 75;
	int card4 = -1;
	int card5 = 0;


	//fill with junk values
	fillArray();


	//add card value to 3 different arrays
	int count = 3;
	testG.deck[thisPlayer][1] = card1;
	testG.hand[thisPlayer][1] = card1;
	testG.discard[thisPlayer][1] = card1;


	//call fullDeckCount function with card value inserted above
	//it should return the count of card in the above three 
	//functions
	test = myAssert(fullDeckCount(thisPlayer, card1, &testG), count); 
	if(test == 1)
		printf("FAIL when one card is in each of the arrays\n");
	else	
		printf("PASS when one card is in each of the arays\n");


	//call with more than one card in one of the arrays
	count = 4;	
	testG.deck[thisPlayer][0] = card2;
	testG.deck[thisPlayer][3] = card2;
	testG.hand[thisPlayer][5] = card2;
	testG.discard[thisPlayer][10] = card2;

	test = myAssert(fullDeckCount(thisPlayer, card2, &testG), count); 
	if(test == 1)
		printf("FAIL when card count is greater than 1 in one of the arrays \n");
	else	
		printf("PASS when card count is greater than 1 in one of the arrays\n");


	//call with more than one card in all of the arrays
	count = 6;
	testG.deck[thisPlayer][3] = card3;
	testG.deck[thisPlayer][4] = card3;
	testG.hand[thisPlayer][15] = card3;
	testG.hand[thisPlayer][16] = card3;
	testG.discard[thisPlayer][45] = card3;
	testG.discard[thisPlayer][46] = card3;

	test = myAssert(fullDeckCount(thisPlayer, card3, &testG), count); 
	if(test == 1)
		printf("FAIL when more than one card is in all of the arrays\n");
	else	
		printf("PASS when more than one card is in all of the arrays\n");
	

	//call with the card not in any of the arrays
	count = 0;	

	test = myAssert(fullDeckCount(thisPlayer, card4, &testG), count); 
	if(test == 1)
		printf("FAIL when card is in none of the arrays\n");
	else	
		printf("PASS when card is in none of the arrays\n");


	//call with cards in one array only
	count = 4;
	testG.discard[thisPlayer][0] = card5;
	testG.discard[thisPlayer][15] = card5;
	testG.discard[thisPlayer][33] = card5;
	testG.discard[thisPlayer][42] = card5;

	test = myAssert(fullDeckCount(thisPlayer, card5, &testG), count); 
	if(test == 1)
		printf("FAIL when cards are in one array\n");
	else	
		printf("PASS when cards are in one array \n");




	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

	return 0;
}
