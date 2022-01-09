#include "PrintFunctions.h"
#include "Card.h"
#include "DeckFunctions.h"

//Prints Deck (EC+), for k rows of 13 cards each, i specifies which part of the card is being printed, and j iterates through the cards 
void PrintDeck(card* pt, int num) {

	int init = 0;
	int done = 0;
	card* pt1 = pt;

	int numCards = 13;

	//sets the number of cards for each row, capped at 13, can be less
	if (CountCards(pt) < 13) {

		numCards = CountCards(pt);

	}

	//this tells us how many rows to do
	for (int k = 0; k < num; ++k) {

		//this prints each part of the card
		for (int i = 1; i <= 5; ++i) {

			//this prints a row of cards
			for (int j = 1; j <= numCards; ++j) {

				//If the card is not A, J, Q, or K
				if ((pt->num != 14) && (pt->num != 11) && (pt->num != 12) && (pt->num != 13)) {

					//If the card is 10
					if (pt->num == 10) {

						if (i == 1) {
							printf(" ----  ");
						}
						else if (i == 2) {
							printf("|%d%c | ", pt->num, pt->suit);
						}
						else if (i == 3) {
							printf("|    | ");
						}
						else if (i == 4) {
							printf("| %d%c| ", pt->num, pt->suit);
						}
						else {
							printf(" ----  ");
						}

					}

					//If the card is 2-9
					else {

						if (i == 1) {
							printf(" ----  ");
						}
						else if (i == 2) {
							printf("|%d%c  | ", pt->num, pt->suit);
						}
						else if (i == 3) {
							printf("|    | ");
						}
						else if (i == 4) {
							printf("|  %d%c| ", pt->num, pt->suit);
						}
						else {
							printf(" ----  ");
						}

					}

				}

				//If the card is A, J, Q, or K
				else {

					if (i == 1) {
						printf(" ----  ");
					}
					else if (i == 2) {
						printf("|%c%c  | ", pt->face, pt->suit);
					}
					else if (i == 3) {
						printf("|    | ");
					}
					else if (i == 4) {
						printf("|  %c%c| ", pt->face, pt->suit);
					}
					else {
						printf(" ----  ");
					}

				}

				//iterates through the cards during times when the value needs to be printed
				if ((i == 2) || (i == 4)) {

					if (pt->next != NULL) {
						pt = pt->next;
					}

				}

				//resets the cards back to 0 so they can be printed again for the bottom right corner of the card
				if (i == 3) {

					pt = pt1;

				}

			}

			//next row of cards formatting
			printf("\n");

			//reset pt1 to be the first card value for the next row of cards
			if (i == 4) {

				pt1 = pt;

			}
		}
	}
}

//Prints the stats (can be customized to hide bot cards)
void printStats(char Name[], card* Player, card* Bot1, card* Bot2, card* Bot3) {

	printf("\n\n%s's Hand has %d cards\n", Name, CountCards(Player));
	SortCards(Player, CountCards(Player));
	PrintDeck(Player, 1);
	printf("%s's Hand has %d cards\n", "Computer 1", CountCards(Bot1));
	SortCards(Bot1, CountCards(Bot1));
	PrintDeck(Bot1, 1);
	printf("%s's Hand has %d cards\n", "Computer 2", CountCards(Bot2));
	SortCards(Bot2, CountCards(Bot2));
	PrintDeck(Bot2, 1);
	printf("%s's Hand has %d cards\n", "Computer 3", CountCards(Bot3));
	SortCards(Bot3, CountCards(Bot3));
	PrintDeck(Bot3, 1);
	printf("\n");

}