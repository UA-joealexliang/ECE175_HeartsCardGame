#ifndef PRINTFUNCTIONS_H
#define PRINTFUNCTIONS_H

#include "Card.h"
#include "DeckFunctions.h"

//Prints Deck (EC+), for k rows of 13 cards each, i specifies which part of the card is being printed, and j iterates through the cards 
void PrintDeck(card* pt, int num);

//Prints the stats (can be customized to hide bot cards)
void printStats(char Name[], card* Player, card* Bot1, card* Bot2, card* Bot3);

#endif PRINTFUNCTIONS_H
