#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "Card.h"
#include "DeckFunctions.h"
#include "PrintFunctions.h"

//Formats Name of Player
void my_fgets(char* str, int max_chars, FILE* fptr);

//Checks to see if hearts has been broken
int IsHeartBroken(card* Table);

//Finds 2 of Clubs to determine who starts the game, if Clubs is found: (1) returns true (2) adds card to Table (3) refresh player deck
int FindStarter(card* playerHeadNode, card* playerTailNode, card* Table);

//Finds the winner of a round
int RoundWinner(char suit, card* Table, int leader, int* playerscore, int* bot1score, int* bot2score, int* bot3score);

//Finds a specific card (used for when playing a card)
card* PlayCard(card* playerHeadNode, int cardPosition, card* Table);

//Main Game Function
void BeginGame(card* TableHead, char Name[], card* Player, card* PlayerTail, card* Bot1, card* Bot2, card* Bot3, int num, char name[]);

//Create the players (Player1, Bot1, Bot2, Bot3) and their cards
void CreatePlayers(card* HeadNode);

//Creating the deck function
void CreateDeck(card* HeadNode, card* TailNode);

#endif GAMEFUNCTIONS_H