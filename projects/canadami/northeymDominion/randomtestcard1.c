/*****************************************************************
 * Author: Michael Canaday
 * Date: 5/13/18
 * Description: This is a random tester program for the village
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
#define TESTCARD "village"

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
				 
	struct gameState *G, *testG;
	
	int x = 0;
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\n");

	for(x = 0; x < 50; x++){ 
	G = malloc(sizeof(struct gameState));
	testG = malloc(sizeof(struct gameState));

	seed = rand() % MAX_DECK;
	numPlayers = (rand() % 4) + 1;
	thisPlayer = numPlayers - 1;
	initializeGame(numPlayers, cards, seed, G);
	memcpy(testG, G, sizeof(struct gameState));

	failure = false;
	int newCards = 1;
	int addedActions = 2;
	int deck = rand() % MAX_DECK;					//set number of cards in deck to random
	int discarded = rand() % (MAX_DECK - deck);		//set number of cards in discard pile to random
	int hand = rand() % (MAX_DECK - discarded);
	int cardEffectReturnValue;
	int expectedReturnValue = 0;
	testG->deckCount[thisPlayer] = deck;
	testG->discardCount[thisPlayer] = discarded;
	testG->handCount[thisPlayer] = hand;
	G->deckCount[thisPlayer] = deck;
	G->discardCount[thisPlayer] = discarded;
	G->handCount[thisPlayer] = hand;

	cardEffectReturnValue = cardEffect(village, choice1, choice2, choice3, testG, handpos, &bonus);

	test = myAssert(cardEffectReturnValue, expectedReturnValue); 
	if(test==1)
	{
		printf("FAIL Card Effect return value when calling %s", TESTCARD);
		printf("%s return value = %d, expected = %d\n", TESTCARD, cardEffectReturnValue, expectedReturnValue);
		failure = true;
	}

	test = myAssert(testG->handCount[thisPlayer], G->handCount[thisPlayer] + newCards); 
	if(test==1)
	{
		printf("%s", "FAIL number of cards in hand test: ");
		printf("hand count = %d, expected = %d\n", testG->handCount[thisPlayer], G->handCount[thisPlayer] + newCards);
		failure = true;
	}
	
	test = myAssert(testG->deckCount[thisPlayer], G->deckCount[thisPlayer] - newCards); 
	if(test==1)
	{
		printf("%s", "FAIL number of cards in deck test: ");
		printf("deck count = %d, expected = %d\n", testG->deckCount[thisPlayer], G->deckCount[thisPlayer] - newCards);
		failure = true;
	}	
	test = myAssert(testG->numActions, G->numActions); 
	if(test==1)
	{
		printf("%s", "FAIL number of actions test: ");
		printf("numActions = %d, expected = %d\n", testG->numActions, G->numActions + addedActions);
		failure = true;
	}

	int cardDrawn;
	int topOfDeck;
	int numCorrectCardsDrawn = 0;	
	int maxHand = 5;

	int actualNewCards = testG->handCount[thisPlayer] - maxHand + discarded;
	int i;

	for(i=0; i<actualNewCards; i++){
		cardDrawn = testG->hand[thisPlayer][testG->handCount[thisPlayer]-1-i];
		topOfDeck = G->deck[thisPlayer][G->deckCount[thisPlayer]-1-i];
		
		test = myAssert(cardDrawn, topOfDeck);
		if(test==1)
		{
			printf("%s", "FAIL to draw correct cards from the deck: ");
			printf("cardDrawn = %d, expected = %d\n", cardDrawn, topOfDeck);
			failure = true;
			break;
		}
		else
		numCorrectCardsDrawn++;
	}

	int j;
	for(i = 0; i < numPlayers; i++){
		thisPlayer = i;
		if(thisPlayer!= 0){
			if(G->handCount[thisPlayer] != testG->handCount[thisPlayer]){
				printf("FAIL state of player %d's hand count\n", i);
				failure = true;
				break;
			}
			else if(G->deckCount[thisPlayer] != testG->deckCount[thisPlayer]){
				printf("FAIL state of player %d's deck count\n", i);
				failure = true;
				break;
			}
			else if(G->discardCount[thisPlayer] != testG->discardCount[thisPlayer]){
				printf("FAIL state of player %d's discard count\n", i);
				failure = true;
				break;
			}

			for(j = 0; j < G->handCount[thisPlayer]; j++){
				if(G->hand[thisPlayer][j] != testG->hand[thisPlayer][j]){
					printf("FAIL state of player %d's hand\n", i);
					failure = true;
					break;
				} 
				if(G->deck[thisPlayer][j] != testG->deck[thisPlayer][j]){
					printf("FAIL state of player %d's deck\n", i);
					failure = true;
					break;
				} 
				if(G->discard[thisPlayer][j] != testG->discard[thisPlayer][j]){
					printf("FAIL state of player %d's discard pile\n", i);
					failure = true;
					break;
				} 
			}
		}
	}

	int pass = 1;
	for(i = 0; i < kingdomCount; i++){
		if(G->supplyCount[cards[i]] != testG->supplyCount[cards[i]]){
			printf("FAIL Kingdom cards supply count\n");				
			failure = true;
			pass--;
		}
	}

	pass = 1;
	for(i = 0; i < victoryCount; i++){
		if(G->supplyCount[victory[i]] != testG->supplyCount[victory[i]]){
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
		printf("----------------------------------------\n\n");
	}

	free(G);
	free(testG);	
	}
	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

return 0;
}
