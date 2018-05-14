/*****************************************************************
 * Author: Michael Canaday
 * Date: 5/13/18
 * Description: This is a random tester for the adventurer 
 *				function.
*****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define TESTFUNCTION "fullDeckCount"
#define TESTCARD "adventurer"

int myAssert(int left, int right){
	if (left != right)
		return 1;
	else 
		return 0; 
}

int main(){
	srand(time(NULL));
	bool failure;
	int test;
	int seed;
	int numPlayers;
	int thisPlayer;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
					 remodel, smithy, village, baron, great_hall};
	int kingdomCount = 10;
	int victory[6] = {estate, duchy, province, curse, gardens, great_hall};			 
	int victoryCount = 6;
				 
	struct gameState G, testG;
	
	int x = 0;
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\n");

	for(x = 0; x < 100; x++){ 
	seed = rand() % 500;
	numPlayers = (rand() % 4) + 1;
	thisPlayer = numPlayers - 1;
	initializeGame(numPlayers, cards, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	failure = false;
	int newCards = 2;
	int deck = rand() % MAX_DECK;					//set number of cards in deck to random
	int discarded = rand() % (MAX_DECK - deck);		//set number of cards in discard pile to random
	int cardEffectReturnValue;
	int expectedReturnValue = 0;
	testG.deckCount[thisPlayer] = deck;
	testG.discardCount[thisPlayer] = discarded;

	cardEffectReturnValue = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	test = myAssert(cardEffectReturnValue, expectedReturnValue); 
	if(test==1)
	{
		printf("FAIL Card Effect return value when calling %s", TESTCARD);
		printf("%s return value = %d, expected = %d\n", TESTCARD, cardEffectReturnValue, expectedReturnValue);
		failure = true;
	}

	int i;
	int cardDrawn = -1;
	int numTestTreasures = 0;

	for(i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		cardDrawn = testG.hand[thisPlayer][i];
		if(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		numTestTreasures++;
	}

	int numTreasures = 0;
	cardDrawn = -1;
	for(i = 0; i < G.handCount[thisPlayer]; i++)
	{
		cardDrawn = G.hand[thisPlayer][i];
		if(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		numTreasures++;
	}

	test = myAssert(numTestTreasures, numTreasures + newCards); 
	if(test==1)
	{
		printf("%s", "FAIL: did not add correct number of treasures to hand: ");
		printf("number of treasures = %d, expected = %d\n", numTestTreasures, numTreasures + newCards);
		failure = true;
	}
	
	int pass = 1;

	for(i = 0; i < kingdomCount; i++)
	{
		if(G.supplyCount[cards[i]] != testG.supplyCount[cards[i]]){
			printf("FAIL Kingdom cards supply count\n");				
			failure = true;
			pass--;
		}
	}

	pass = 1;
	for(i = 0; i < victoryCount; i++)
	{
		if(G.supplyCount[victory[i]] != testG.supplyCount[victory[i]]){
			printf("FAIL Victory cards supply count\n");
			failure = true;
			pass--;
		}
	}
	
	if(failure){
		printf("\n");
		printf("Seed: %d, ", seed);
		printf("numPlayers: %d, ", numPlayers);
		printf("thisPlayer: %d, ", thisPlayer);
		printf("Deck Count: %d, ", deck);
		printf("Discard Count: %d\n\n", discarded);
		printf("-------------------------------------\n\n");
	}
	
	}
	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

return 0;
}
