#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "supplyCount"

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


	int value = 0;
	int pass = 1;
	for(i = 0; i < 27; i++)
	{
		testG.supplyCount[i] = value;
		test = myAssert(supplyCount(i, &testG), value); 
		if(test == 1){
			printf("FAIL on card = %d\n", i);
			printf("count is: %d ", supplyCount(i, &testG));
			printf("expected: %d\n", value);
			pass--;
		}
	}
	if(pass == 1)
		printf("PASS when value  = 0\n");
	
	value = 7;
	for(i = 0; i < 27; i++)
	{
		testG.supplyCount[i] = value;
		test = myAssert(supplyCount(i, &testG), value); 
		if(test == 1){
			printf("FAIL on card = %d\n", i);
			printf("count is: %d ", supplyCount(i, &testG));
			printf("expected: %d\n", value);
			pass--;
		}
	}
	if(pass == 1)	
		printf("PASS when value = 7\n");
	

	
	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

	return 0;
}
