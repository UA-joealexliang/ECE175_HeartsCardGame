#define _CRT_SECURE_NO_WARNINGS
#include "Card.h"
#include "GameFunctions.h"
#include "DeckFunctions.h"
#include "PrintFunctions.h"

int main(void) {

	srand((int)time(0)); //seed the RNG
	char userKey = 'y';

	do {

		card* HeadNode = NULL;
		card* TailNode = NULL;
		CreateDeck(HeadNode, TailNode);

		printf("\nDo you want to play another game? (q to quit) ");
		scanf(" %c", &userKey);

	} while (userKey != 'q');//While the user wants to play

	return 0;
}