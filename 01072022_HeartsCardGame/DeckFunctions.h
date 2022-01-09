#ifndef DECKFUNCTIONS_H
#define DECKFUNCTIONS_H

#include "Card.h"

/*Single card functions*/

//Return position from deck given card suit and num
int FindPositionFromCard(card* HeadNode, int suit, int num);

//Finds the suit of a card given position
char FindSuitFromPosition(card* HeadNode, int cardPosition);

//Adds swapped card from HeadNode of PlayerN to tail of PlayerN+1 (used for when swapping three cards)
card* ReturnNextPlayerTailNodeFromSwap(card* Player1HeadNode, int cardPosition, card* Player2TailNode, int init);

//Function that looks for the major cards in the deck
void FindBiggestAndSmallestCard(card* Bot, int* Heart, int* Diamond, int* Club, int* Spade, int* sHeart, int* sDiamond, int* sClub, int* sSpade, int* ValueH, int* ValueD, int* ValueC, int* ValueS, int* sValueH, int* sValueD, int* sValueC, int* sValueS);

//Finds the specified card
int FindCard(card* Bot, card* Table, int Player, int HeartBroken, int starter, int tempwinner, int end, int suit, int tempwinnernum);

//Checks entered value to make sure it is within the range
int CheckValidNum(card* HeadNode, card* TailNode, int Card1, int Card2, int Card3, int numPlayer, card* Bot1, card* Bot2, card* Bot3, card* Bot1Tail, card* Bot2Tail, card* Bot3Tail);


/*Full deck functions*/

//Card Counting Function: counts number of cards in a deck
int CountCards(card* HeadNode);

//Card Sorting Function (EC+): sorts card by suit, then by value for easy readibility
void SortCards(card* HeadNode, int numCards);

//Shuffling Deck Function
void ShuffleDeck(card* HeadNode, card* TailNode);

#endif DECKFUNCTIONS_H