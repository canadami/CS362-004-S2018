#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver"

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
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 
	struct gameState G, testG;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, cards, seed, &G);
	//copy gamestate to testG
	memcpy(&testG, &G, sizeof(struct gameState));	
	
	printf("----------------- Testing Card: %s ----------------\n", TESTFUNCTION);
	printf("\n");


	//set count of provinces to 5
	testG.supplyCount[province] = 5;
	
	//check if isGameOver returns 0
	test = myAssert(isGameOver(&testG), 0);
	if(test == 1)
		printf("FAIL when province count is 5\n");
	else
		printf("PASS when province count is 5\n");

	
	//set count of provinces to 0
	testG.supplyCount[province] = 0;
	
	//check if isGameOver returns 1
	test = myAssert(isGameOver(&testG), 1);
	if(test == 1)
		printf("FAIL when province count is 0\n");
	else
		printf("PASS when province count is 0\n");
	

	testG.supplyCount[province] = 1;
	
	//add one card to all supply cards
	for(i = 0; i < 25; i++)
	{
		testG.supplyCount[i] = 1;
	}
	
	//check if isGameOver returns 0
	test = myAssert(isGameOver(&testG), 0);
	if(test == 1)
		printf("FAIL when all decks contain 1 card\n");
	else
		printf("PASS when all decks contain 1 card\n");
	
	
	//empty 1 deck
	testG.supplyCount[10] = 0;
	//check if isGameOver returns 0
	test = myAssert(isGameOver(&testG), 0);
	if(test == 1)
		printf("FAIL when one deck is empty\n");
	else
		printf("PASS when one deck is empty\n");
	
	//empty second deck
	testG.supplyCount[17] = 0;
	//check if isGameOver returns 0
	test = myAssert(isGameOver(&testG), 0);
	if(test == 1)
		printf("FAIL when two decks are empty\n");
	else
		printf("PASS when two decks are empty\n");
	
	//empty third deck
	testG.supplyCount[19] = 0;
	//check if isGameOver returns 1
	test = myAssert(isGameOver(&testG), 1);
	if(test == 1)
		printf("FAIL when three decks are empty\n");
	else
		printf("PASS when three decks are empty\n");
	
	//empty four more decks
	testG.supplyCount[11] = 0;
	testG.supplyCount[12] = 0;
	testG.supplyCount[13] = 0;
	testG.supplyCount[15] = 0;
	//check if isGameOver returns 1
	test = myAssert(isGameOver(&testG), 1);
	if(test == 1)
		printf("FAIL when seven decks are empty\n");
	else
		printf("PASS when seven decks are empty\n");
	
	

	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

	return 0;
}
