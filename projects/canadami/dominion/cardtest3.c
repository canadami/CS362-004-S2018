#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

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
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 
	struct gameState G, testG;
	
	// initialize a game state and player cards
	initializeGame(numPlayers, cards, seed, &G);
	//copy gamestate to testG
	memcpy(&testG, &G, sizeof(struct gameState));	
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\n");

	int newCards = 4;
	int addedBuy = 1;
	int otherPlayersNewCards = 1;
	int otherPlayersDiscarded= 0;
	int discarded = 1;
	int shuffleCards = 0;
	int cardEffectReturnValue;
	int expectedReturnValue = 0;

	//call function in cardEffect
	cardEffectReturnValue = cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);


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


	//verify that a buy has been added to the player's buy count
	test = myAssert(testG.numBuys, G.numBuys); 
	if(test==1)
	{
		printf("%s", "FAIL number of buys test: ");
		printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + addedBuy);
	}
	else
	printf("%s\n", "PASS number of buys test");
	
	
	int cardDrawn;
	int topOfDeck;
	int numCorrectCardsDrawn = 0;	
	int maxHand = 5;

	//calculate how many cards were actually drawn
	int actualNewCards = testG.handCount[thisPlayer] - maxHand + discarded;

	//loop through the cards drawn in the hand(after drawing), and also the deck(before drawing)
	//if they are not the same, then cards are not being drawn correctly from the deck

	
	for(i=0; i<actualNewCards; i++)
	{
		cardDrawn = testG.hand[thisPlayer][testG.handCount[thisPlayer]-1-i];
		topOfDeck = G.deck[thisPlayer][G.deckCount[thisPlayer]-1-i];
		
		test = myAssert(cardDrawn, topOfDeck);
		if(test==1)
		{
			printf("%s", "FAIL: did not draw correct cards from the deck: ");
			printf("cardDrawn = %d, expected = %d\n", cardDrawn, topOfDeck);
			break;
		}
		else
		numCorrectCardsDrawn++;
	}
	if(numCorrectCardsDrawn == actualNewCards)
		printf("%s\n", "PASS draw correct cards from deck test");
	

	//compare number of cards in the other players' hands before and after using the card
	for(i = 0; i < testG.numPlayers; i++)
	{
		if(i != thisPlayer)
		{
			test = myAssert(testG.handCount[i], G.handCount[i] + otherPlayersNewCards - otherPlayersDiscarded); 
			if(test==1)
			{
				printf("%s", "FAIL number of cards in other players' hands test: ");
				printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i] + newCards - discarded);
			}
			else
			printf("%s\n", "PASS number of cards in other players' hands test");	
		}
	}

	
	int otherPlayer;
	numCorrectCardsDrawn = 0;
	
	for(otherPlayer = 0; otherPlayer < numPlayers; otherPlayer++)
	{
		if(otherPlayer != thisPlayer)
		{
			//calculate how many cards were actually drawn
			actualNewCards = testG.handCount[otherPlayer];

			//loop through the cards drawn in the hand(after drawing), and also the deck(before drawing)
			//if they are not the same, then cards are not being drawn correctly from the deck
			for(i=0; i<actualNewCards; i++)
			{
				cardDrawn = testG.hand[otherPlayer][testG.handCount[otherPlayer]-1-i];
				topOfDeck = G.deck[otherPlayer][G.deckCount[otherPlayer]-1-i];
			
				test = myAssert(cardDrawn, topOfDeck);
				if(test==1)
				{
					printf("FAIL to draw correct cards from other Player: %d's deck: ", otherPlayer);
					printf("cardDrawn = %d, expected = %d\n", cardDrawn, topOfDeck);
					break;
				}
				else
				numCorrectCardsDrawn++;
			}
			if(numCorrectCardsDrawn == actualNewCards)
				printf("%s\n", "PASS draw correct cards from other players' deck test");
		}
	}
		
	printf("\n");
	printf("----------------- Test Completed Successfully----------------\n");
	printf("\n");

	return 0;
}
