#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struct with fancy suit character for J, Q, K, and A
typedef struct card_s {
	char suit; //
	int num; //2-10
	char face; //J, Q, K, A
	struct card_s* next; //next card in the deck
} card;

#endif CARD_H