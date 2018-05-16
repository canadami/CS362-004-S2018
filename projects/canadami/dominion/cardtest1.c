#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

//assert two values are equal
int myAssert(int left, int right)
{
	if(left != right)
		return 1;
	
	return 0;
}

int main()
{
	int test;
	int seed = 99;
	int numPlayers = 2;
	int thisPlayer = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
	int kingdomCount = 10;
	int victory[6] = {estate, duchy, province, curse, gardens, great_hall};			 
	int victoryCount = 6;
				 
	struct gameState G, testG;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, cards, seed, &G);
	//copy gamestate to testG
	memcpy(&testG, &G, sizeof(struct gameState));	
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\n");

	int newCards = 2;
	int discarded = 1;
	int shuffleCards = 0;
	int cardEffectReturnValue;
	int expectedReturnValue = 0;

	//call function in cardEffect
	cardEffectReturnValue = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//check return value of function against expected value
	test = myAssert(cardEffectReturnValue, expectedReturnValue); 
	if(test==1)
	{
		printf("FAIL Card Effect return value when calling %s", TESTCARD);
		printf("%s return value = %d, expected = %d\n", TESTCARD, cardEffectReturnValue, expectedReturnValue);
	}
	else
	printf("%s\n", "PASS Card Effect return value");	

	//compare number of cards in player's hand before and after using the card 
	test = myAssert(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded); 
	if(test==1)
	{
		printf("%s", "FAIL number of cards in hand test: ");
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	}
	else
	printf("%s\n", "PASS number of cards in hand test");	

	//compare number of cards in the player's deck before and after using the card
	test = myAssert(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffleCards); 
	if(test==1)
	{
		printf("%s", "FAIL number of cards in deck test: ");
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffleCards);
	}
	else
	printf("%s\n", "PASS number of cards in deck test");


	int i;
	int cardDrawn = -1;
	int numTestTreasures = 0;

	//loop through the player's test hand (after using adventurer)
	//There should be two more treasures than before
	for(i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		cardDrawn = testG.hand[thisPlayer][i];
		if(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		numTestTreasures++;
	}

	//loop through the player's test hand (before using adventurer)
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
		printf("number of treasures = %d, expected = %d\n", numTestTreasures, numTreasures);
	}
	else
	printf("%s\n", "PASS number of treasures in hand test");
	

	int j;
	//Check other players' state to make sure it has not changed
	for(i = 0; i < numPlayers; i++)
	{
		thisPlayer = i;
		if(thisPlayer!= 0)
		{
			if(G.handCount[thisPlayer] != testG.handCount[thisPlayer]){
				printf("FAIL state of player %d's hand count\n", i);
				break;
			}
			else if(G.deckCount[thisPlayer] != testG.deckCount[thisPlayer]){
				printf("FAIL state of player %d's deck count\n", i);
				break;
			}
			else if(G.discardCount[thisPlayer] != testG.discardCount[thisPlayer]){
				printf("FAIL state of player %d's discard count\n", i);
				break;
			}	
			else
				printf("PASS count of player %d's hand, deck, discard arrays\n", i);			

			
			for(j = 0; j < G.handCount[thisPlayer]; j++)
			{
				if(G.hand[thisPlayer][j] != testG.hand[thisPlayer][j])
				{
					printf("FAIL state of player %d's hand\n", i);
					break;
				} 
				if(G.deck[thisPlayer][j] != testG.deck[thisPlayer][j])
				{
					printf("FAIL state of player %d's deck\n", i);
					break;
				} 
				if(G.discard[thisPlayer][j] != G.discard[thisPlayer][j])
				{
					printf("FAIL state of player %d's discard pile\n", i);
					break;
				} 
			} 
			printf("PASS state of player %d's hand, deck, discard arrays\n", i);
		}
	}	


	int pass = 1;
	//Check if the kingdom or victory cards have been changed
	for(i = 0; i < kingdomCount; i++)
	{
		if(G.supplyCount[cards[i]] != testG.supplyCount[cards[i]]){
			printf("FAIL Kingdom cards supply count\n");				
			pass--;
		}
	}
	if(pass == 1)
		printf("PASS Kingdom cards supply count\n");


	pass = 1;
	for(i = 0; i < victoryCount; i++)
	{
		if(G.supplyCount[victory[i]] != testG.supplyCount[victory[i]]){
			printf("FAIL Victory cards supply count\n");
			pass--;
		}
	}
	if(pass == 1)
		printf("PASS Victory cards supply count\n");

	
	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

	return 0;
}
