#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "scoreFor"

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


	
	
void fillWithJunk(){	
	//fill player's hand with junk values
	for(i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = -99;
	}
	 
	//fill player's discard pile with junk values
	for(i = 0; i < testG.discardCount[thisPlayer]; i++)
	{
		testG.discard[thisPlayer][i] = -99;
	}
	 	
	//fill player's hand with junk values
	for(i = 0; i < testG.deckCount[thisPlayer]; i++)
	{
		testG.deck[thisPlayer][i] = -99;
	}
}


	//set size of player's hand, discard pile, and deck
	testG.handCount[thisPlayer] = 10;
	testG.discardCount[thisPlayer] = 10;
	testG.deckCount[thisPlayer] = 10;
	fillWithJunk();	
	
	//add one estate card to the hand only
	testG.hand[thisPlayer][8] = estate;
	int expectedScore = 1;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL when one estate is in hand: ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS when one estate is in hand\n");
	

	fillWithJunk();	

	//add one estate card to the discard only 
	testG.discard[thisPlayer][8] = estate;
	expectedScore = 1;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL when one estate is in discard: ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS when one estate is in discard\n");


	fillWithJunk();	
	
	//add one estate card to the deck only 
	testG.deck[thisPlayer][8] = estate;
	expectedScore = 1;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL when one estate is in deck: ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS when one estate is in deck\n");

	
	//set size of player's hand, discard pile, and deck
	testG.handCount[thisPlayer] = 50;
	testG.discardCount[thisPlayer] = 50;
	testG.deckCount[thisPlayer] = 50;
	fillWithJunk();
	
	//add one estate card to the hand and discard pile
	testG.hand[thisPlayer][14] = estate;
	testG.discard[thisPlayer][4] = estate;
	expectedScore = 2;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL when one estate in hand, discard each: ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS when one estate in hand, discard each\n");
		
	
	//add one estate card to the hand 
	testG.deck[thisPlayer][4] = estate;
	expectedScore = 3;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL when one estate in hand, discard, deck each: ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS when one estate in hand, discard, deck each\n");
	
	
	fillWithJunk();
	
	//no cards of any value are in the hand
	expectedScore = 0;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL with no victory cards: ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS with no victory cards\n");
	
	
	//value of victory cards is negative
	testG.hand[thisPlayer][9] = curse;
	testG.discard[thisPlayer][11] = curse;
	testG.deck[thisPlayer][12] = curse;
	expectedScore = -3;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL with negative score (3 curse cards): ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS with negative score (3 curse cards)\n");
	
	
	//fill arrays with junk
	fillWithJunk();	
	//change size to 10
	testG.handCount[thisPlayer] = 13;
	testG.discardCount[thisPlayer] = 13;
	testG.deckCount[thisPlayer] = 13;
	
	//all three arrays contain a total of 13 cards between them, one being gardens
	testG.hand[thisPlayer][0] = -99;
	testG.hand[thisPlayer][1] = -99;
	testG.deck[thisPlayer][2] = -99;
	testG.hand[thisPlayer][3] = gardens;
	testG.hand[thisPlayer][4] = -99;
	testG.hand[thisPlayer][5] = -99;
	testG.discard[thisPlayer][6] = -99;
	testG.hand[thisPlayer][7] = -99;
	testG.hand[thisPlayer][8] = -99;
	testG.hand[thisPlayer][9] = -99;
	testG.deck[thisPlayer][12] = -99;
	testG.hand[thisPlayer][11] = -99;
	testG.discard[thisPlayer][12] = -99;
	


	expectedScore = 1;
	test = myAssert(scoreFor(thisPlayer, &testG), expectedScore); 
	if(test == 1){
		printf("FAIL test with one garden card and 13 cards total: ");
		printf("score is: %d; expected: 1\n", scoreFor(thisPlayer, &testG));	
	}
	else	
		printf("PASS test with one garden card and 13 cards total: \n");


	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

	return 0;
}
