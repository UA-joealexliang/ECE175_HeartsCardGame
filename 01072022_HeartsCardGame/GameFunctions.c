#define _CRT_SECURE_NO_WARNINGS
#include "Card.h"
#include "DeckFunctions.h"
#include "PrintFunctions.h"

//Formats Name of Player
void my_fgets(char* str, int max_chars, FILE* fptr) {
	fgets(str, max_chars, fptr);
	//Makes sure to not count \n or a space as beginning of the name
	while ((str[0] == '\n') || (str[0] == ' ')) {
		fgets(str, 23, stdin);
	}
	//sets last character to be the last character in the name
	if (str[strlen(str) - 1] == '\n') {
		str[strlen(str) - 1] = '\0';
	}
}

//Checks to see if hearts has been broken
int IsHeartBroken(card* Table) {
	int broken = 0;
	for (int i = 1; i <= 4; ++i) {
		if (Table->suit == 3) {
			broken = 1;
		}
		else {
			Table = Table->next;
		}

	}

	return broken;
}

//Finds 2 of Clubs to determine who starts the game, if Clubs is found: (1) returns true (2) adds card to Table (3) refresh player deck
int FindStarter(card* playerHeadNode, card* playerTailNode, card* Table) {

	int cardPosition = 1;
	int found = 0;
	int init = 0;
	int done = 0;
	card* tempNode = playerHeadNode;
	card* beforeNode = playerHeadNode;

	while (done == 0) {

		//if card is 2 of clubs, add card to table and set found = 1
		if (tempNode->num == 2) {

			if (tempNode->suit == 5) {

				found = 1;
				done = 1;

				Table->num = 2;
				Table->suit = 5;
				Table->next = NULL;

			}

		}

		//if not found, keep iterating till last card in deck
		if (found == 0) {

			if (init == 1) {

				beforeNode = beforeNode->next;

			}

			if (tempNode->next != NULL) {

				tempNode = tempNode->next;
				init = 1;
				cardPosition = cardPosition + 1;

			}

			else {

				done = 1;

			}

		}

	}

	//if found and 2 of Clubs is the first card of the deck, redefine playerHeadNode
	if ((found == 1) && (cardPosition == 1)) {

		*playerHeadNode = *playerHeadNode->next;

	}

	//if found and 2 of Clubs is somewhere in the middle of the deck, fix gap
	else if ((found == 1) && (cardPosition != 13)) {

		beforeNode->next = tempNode->next;

	}

	//if found and 2 of Clubs is the last card, redefine playerTailNode
	else if ((found == 1) && (cardPosition == 13)) {

		card* tempNode = NULL;
		tempNode = playerHeadNode;

		for (int i = 1; i < 13; ++i) {

			tempNode = tempNode->next;

		}

		playerTailNode = tempNode;

	}

	return found;
}

//Finds the winner of a round
int RoundWinner(char suit, card* Table, int leader, int* playerscore, int* bot1score, int* bot2score, int* bot3score) {

	int found = 0;
	int winner = leader; //winner is set to the first person to lead a card
	int num;
	num = Table->num; //The face value of the first card placed
	card* tempTableNode = Table;
	int score = 0; //keeps track of points for the round

	for (int i = 0; i < 4; ++i) {

		//If the card is of the same suit as the leading card and its face value is higher, update the highest value
		if ((tempTableNode->suit == suit) && (tempTableNode->num > num)) {

			num = tempTableNode->num;
			winner = leader;

		}

		//if the card is a queen of spades, penalize 13 points
		if ((tempTableNode->num == 12) && (tempTableNode->suit == 6)) {

			score = score + 13;

		}

		//if the card is of suit hearts, then penalize 1 point
		if (tempTableNode->suit == 3) {

			score = score + 1;

		}

		//iterate through the table
		if (tempTableNode->next != NULL) {
			tempTableNode = tempTableNode->next;
		}

		//update the leader to the next person
		leader = leader + 1;

		if (leader == 4) {

			leader = 0;

		}

	}

	//whoever wins will take score amount of penalty points
	switch (winner)
	{
	case 0:
		*playerscore = *playerscore + score;
		break;

	case 1:
		*bot1score = *bot1score + score;
		break;

	case 2:
		*bot2score = *bot2score + score;
		break;

	case 3:
		*bot3score = *bot3score + score;
		break;

	default:
		break;
	}

	return winner;
}

//Finds a specific card (used for when playing a card)
card* PlayCard(card* playerHeadNode, int cardPosition, card* Table) {

	card* temp = NULL;
	temp = (card*)malloc(sizeof(card));

	card* Save = playerHeadNode;
	card* Target = playerHeadNode;
	card* Prev = playerHeadNode;

	//iterates until the user chosen card
	for (int i = 1; i < cardPosition; ++i) {

		Target = Target->next;

		if (i > 1) {

			Save = Save->next;
			Prev = Prev->next;

		}

	}

	//Adds to the tail of the table
	if (Table != NULL) {

		Table->next = temp;
		Table->next->face = Target->face;
		Table->next->suit = Target->suit;
		Table->next->num = Target->num;
		Table = Table->next;

	}

	else {

		Table = temp;
		Table->face = Target->face;
		Table->suit = Target->suit;
		Table->num = Target->num;

	}

	//Points card before the target to the card after target
	if ((cardPosition != CountCards(playerHeadNode)) && (cardPosition != 1)) {

		Prev->next = Target->next;

	}

	else if ((cardPosition == 1) && (CountCards(playerHeadNode) != 1)) {
		*playerHeadNode = *playerHeadNode->next;

	}

	else if ((cardPosition == CountCards(playerHeadNode)) && (CountCards(playerHeadNode) != 1)) {

		Prev->next = NULL;

	}

	Table->next = NULL;

	return Table;
}

//Main Game Function //FIXME
void BeginGame(card* TableHead, char Name[], card* Player, card* PlayerTail, card* Bot1, card* Bot2, card* Bot3, int num, const char name[]) {

	//Table Node (cards being played)
	card* TableH = NULL;
	TableHead->next = TableH;

	//scores of the players
	int scorePlayer = 0;
	int scoreBot1 = 0;
	int scoreBot2 = 0;
	int scoreBot3 = 0;
	int init = 0;
	int chosen;

	printf("Round 1\n\n");

	//Print function for whoever is playing the 2 of Spades
	if ((num == 0) && (init == 0)) {

		printf("%s will lead with 2%c\n", name, 5);
		init = 1;
		num = num + 1;

	}

	else {

		printf("%s will lead with 2%c\n", name, 5);

		init = 1;

		if (num != 3) {

			num = num + 1;

		}

		else {

			num = 0;

		}


	}

	int end = 3;//how many cards can be played for each round (starts at 3 because 2 Spades has been initialized)
	int HeartBroken = 0;//Has hearts been broken
	int HeartBrokenprinted = 0;//Has hearts broken been printed already
	int matches = 1;//starts at match 1
	int tempwinnernum = 0;//winning number 
	int tempwinner = num;//winning player
	char suit = 0;//leading suit

	//13 round game
	while (matches != 14) {
		int finished = 0;
		if (matches != 1) {
			printf("Round %d\n\n", matches);
		}
		for (int i = 0; i < end; ++i) {

			if ((init == 1) && (num == 0)) {

				int valid = 1;

				if (CountCards(Player) > 1) {

					printf("Choose a card to play\n");

					do {
						valid = 1;


						printf("Enter a card number between 1-%d where 1 is the leftmost card: ", CountCards(Player));
						scanf("%d", &chosen);

						if (chosen < 1) {

							valid = 0;
							printf("Card number must be greater than 0\n");

						}

						else if (chosen > CountCards(Player)) {

							valid = 0;
							printf("Card number must be less than or equal to %d\n", CountCards(Player));

						}

						//if it is the first play of the round and hearts hasn't been broken
						else if ((i == 0) && (end == 4) && (HeartBroken == 0) && (valid == 1)) {

							char chosensuit = FindSuitFromPosition(Player, chosen);

							if (chosensuit == 3) {
								valid = 0;
								printf("You cannot play %c because it has not been broken\n", 3);
							}

						}

						//if the chosen card is not of the leading suit
						else if ((chosen <= CountCards(Player)) && (chosen > 0) && (valid == 1)) {

							if (FindCard(Player, TableHead, num, HeartBroken, i, tempwinner, end, suit, tempwinnernum) != 0) {

								char chosensuit = FindSuitFromPosition(Player, chosen);

								if (((chosensuit != TableHead->suit) && (i != 0)) || ((chosensuit != TableHead->suit) && (i == 0) && (end == 3))) {

									valid = 0;
									printf("Card with suit %c must be played\n", TableHead->suit);

								}

							}
						}

					} while (valid == 0);

				}

				if (valid == 1) {

					if (CountCards(Player) > 1) {
						TableH = PlayCard(Player, chosen, TableH);
					}
					else {
						chosen = 1;
						TableH = PlayCard(Player, 1, TableH);
					}

					if (i > 0) {

						if ((TableH->suit == suit) && (TableH->num > tempwinnernum)) {

							tempwinnernum = TableH->num;
							tempwinner = num;

						}

					}

					else if (i == 0) {

						tempwinnernum = TableH->num;
						tempwinner = num;
						suit = TableH->suit;

					}

					if (TableH->num > 10) {
						printf("%s plays %c%c\n", Name, TableH->face, TableH->suit);


					}
					else {
						printf("%s plays %d%c\n", Name, TableH->num, TableH->suit);
					}

					num = num + 1;

				}

			}

			else {

				if (num == 1) {

					int Search = FindCard(Bot1, TableHead, num, HeartBroken, i, tempwinner, end, suit, tempwinnernum);
					TableH = PlayCard(Bot1, Search, TableH);

					if (i > 0) {

						if ((TableH->suit == suit) && (TableH->num > tempwinnernum)) {

							tempwinnernum = TableH->num;
							tempwinner = num;

						}

					}

					else if (i == 0) {

						tempwinnernum = TableH->num;
						tempwinner = num;
						suit = TableH->suit;

					}

					if (TableH->num > 10) {
						printf("Computer 1 plays %c%c\n", TableH->face, TableH->suit);
					}
					else {
						printf("Computer 1 plays %d%c\n", TableH->num, TableH->suit);
					}

				}

				else if (num == 2) {

					int Search = FindCard(Bot2, TableHead, num, HeartBroken, i, tempwinner, end, suit, tempwinnernum);
					TableH = PlayCard(Bot2, Search, TableH);

					if (i > 0) {

						if ((TableH->suit == suit) && (TableH->num > tempwinnernum)) {

							tempwinnernum = TableH->num;
							tempwinner = num;

						}

					}

					else if (i == 0) {

						tempwinnernum = TableH->num;
						tempwinner = num;
						suit = TableH->suit;

					}

					if (TableH->num > 10) {
						printf("Computer 2 plays %c%c\n", TableH->face, TableH->suit);
					}
					else {
						printf("Computer 2 plays %d%c\n", TableH->num, TableH->suit);
					}

				}

				else if (num == 3) {

					int Search = FindCard(Bot3, TableHead, num, HeartBroken, i, tempwinner, end, suit, tempwinnernum);
					TableH = PlayCard(Bot3, Search, TableH);

					if (i > 0) {

						if ((TableH->suit == suit) && (TableH->num > tempwinnernum)) {

							tempwinnernum = TableH->num;
							tempwinner = num;

						}

					}

					else if (i == 0) {

						tempwinnernum = TableH->num;
						tempwinner = num;
						suit = TableH->suit;

					}

					if (TableH->num > 10) {
						printf("Computer 3 plays %c%c\n", TableH->face, TableH->suit);
					}
					else {
						printf("Computer 3 plays %d%c\n", TableH->num, TableH->suit);
					}

				}

				if (num != 3) {

					num = num + 1;

				}

				else {

					num = 0;

				}

			}


			if (end == 3) {

				if (TableHead->next == NULL) {
					TableHead->next = TableH;
				}

			}

			if ((end == 4) && (finished == 0)) {

				*TableHead = *TableHead->next;
				TableHead = TableH;
				finished = 1;

			}

		}

		if (HeartBroken == 0) {
			HeartBroken = IsHeartBroken(TableHead);
		}
		if ((HeartBroken == 1) && (HeartBrokenprinted == 0)) {
			printf("Hearts has been broken!\n");
			HeartBrokenprinted = 1;
		}

		PrintDeck(TableHead, 1);
		num = RoundWinner(TableHead->suit, TableHead, num, &scorePlayer, &scoreBot1, &scoreBot2, &scoreBot3);
		if (num == 0) {
			printf("%s won the hand!\n", Name);
		}
		else {
			printf("Computer %d won the hand!\n", num);
		}
		if (matches != 13) {
			printStats(Name, Player, Bot1, Bot2, Bot3);
			TableH = TableHead;
			TableH->next = NULL;
		}

		printf("\n%s has %d points, Computer 1 has %d points, Computer 2 has %d points, Computer 3 has %d points\n", Name, scorePlayer, scoreBot1, scoreBot2, scoreBot3);

		/*printf("\nPress Enter To Continue");
		char enter;

		do {

			fgets(" %c", &enter);

		} while (enter != '\n');*/

		end = 4;
		matches = matches + 1;

	}

	if ((scorePlayer < scoreBot1) && (scorePlayer < scoreBot2) && (scorePlayer < scoreBot3)) {

		printf("%s WINS!", Name);

	}

	else if ((scoreBot1 < scorePlayer) && (scoreBot1 < scoreBot2) && (scoreBot1 < scoreBot3)) {

		printf("Computer 1 WINS!");

	}

	else if ((scoreBot2 < scorePlayer) && (scoreBot2 < scoreBot1) && (scoreBot2 < scoreBot3)) {

		printf("Computer 2 WINS!");

	}

	else if ((scoreBot3 < scorePlayer) && (scoreBot3 < scoreBot1) && (scoreBot3 < scoreBot2)) {

		printf("Computer 3 WINS!");

	}

	else {

		printf("Tie Game!");

	}

}

//Create the players (Player1, Bot1, Bot2, Bot3) and their cards //FIXME
void CreatePlayers(card* HeadNode) {

	char Name[20];

	printf("\nEnter your name: ");
	my_fgets(Name, 20, stdin);
	printf("\n***---*** ***---*** ***---***\n");
	printf("%s, let's play Hearts", Name);
	printf("\n***---*** ***---*** ***---***\n");

	card* nextCard = NULL;
	card* nextCard1 = NULL;
	card* nextCard2 = NULL;
	card* nextCard3 = NULL;
	card* Chosen = HeadNode;
	card* Chosen1 = HeadNode->next;
	card* Chosen2 = HeadNode->next->next;
	card* Chosen3 = HeadNode->next->next->next;
	card* Player = Chosen;
	card* Bot1 = Chosen->next;
	card* Bot2 = Chosen->next->next;
	card* Bot3 = Chosen->next->next->next;

	//Code that gives each player the fourth card from their first card
	for (int i = 1; i < 13; ++i) {

		for (int j = 0; j < 4; ++j) {

			Chosen = Chosen->next;
			Chosen1 = Chosen1->next;
			Chosen2 = Chosen2->next;
			Chosen3 = Chosen3->next;

		}

		if (nextCard == NULL) {

			nextCard = Chosen;
			nextCard1 = Chosen1;
			nextCard2 = Chosen2;
			nextCard3 = Chosen3;
			Player->next = nextCard;
			Bot1->next = nextCard1;
			Bot2->next = nextCard2;
			Bot3->next = nextCard3;

		}

		else {

			nextCard->next = Chosen;
			nextCard = Chosen;
			nextCard1->next = Chosen1;
			nextCard1 = Chosen1;
			nextCard2->next = Chosen2;
			nextCard2 = Chosen2;
			nextCard3->next = Chosen3;
			nextCard3 = Chosen3;

		}

	}

	card* PlayerTail = nextCard;
	nextCard->next = NULL;
	card* Bot1Tail = nextCard1;
	nextCard1->next = NULL;
	card* Bot2Tail = nextCard2;
	nextCard2->next = NULL;
	card* Bot3Tail = nextCard3;
	nextCard3->next = NULL;

	printStats(Name, Player, Bot1, Bot2, Bot3);
	int Card1, Card2, Card3;
	int valid;

	do {

		printf("Choose three cards to give away\n");
		printf("Enter card number between 1-%d where 1 is the leftmost card: ", CountCards(Player));
		scanf("%d%d%d", &Card1, &Card2, &Card3);

		valid = CheckValidNum(Player, PlayerTail, Card1, Card2, Card3, CountCards(Player), Bot1, Bot2, Bot3, Bot1Tail, Bot2Tail, Bot3Tail);

	} while (valid == 0);

	if (valid == 1) {

		printStats(Name, Player, Bot1, Bot2, Bot3);

		card* TableHead = NULL;
		TableHead = (card*)malloc(sizeof(card));

		int player = FindStarter(Player, PlayerTail, TableHead);
		int bot1 = FindStarter(Bot1, Bot1Tail, TableHead);
		int bot2 = FindStarter(Bot2, Bot2Tail, TableHead);
		int bot3 = FindStarter(Bot3, Bot3Tail, TableHead);

		if (player == 1) {

			BeginGame(TableHead, Name, Player, PlayerTail, Bot1, Bot2, Bot3, 0, Name);

		}

		else if (bot1 == 1) {

			BeginGame(TableHead, Name, Player, PlayerTail, Bot1, Bot2, Bot3, 1, "Computer 1");

		}

		else if (bot2 == 1) {

			BeginGame(TableHead, Name, Player, PlayerTail, Bot1, Bot2, Bot3, 2, "Computer 2");

		}

		else if (bot3 == 1) {

			BeginGame(TableHead, Name, Player, PlayerTail, Bot1, Bot2, Bot3, 3, "Computer 3");

		}

	}

	free(HeadNode);

}

//Creating the deck function //FIXME
void CreateDeck(card* HeadNode, card* TailNode) {

	TailNode = (card*)malloc(sizeof(card));
	int counter = 0; //this keeps track of which suit it is

	for (int i = 2; i <= 14; ++i) {
		card* nextCard;
		nextCard = (card*)malloc(sizeof(card)); //allocate memory for each card

		//Initializes Deck
		if (HeadNode == NULL) {
			HeadNode = nextCard;
			HeadNode->next = TailNode;
		}
		nextCard->num = i;//assigns a number to the card 2-14\

		//Assign a suit to the card
		if (counter == 0) {
			nextCard->suit = 3;//hearts
		}
		else if (counter == 1) {
			nextCard->suit = 4;//diamonds
		}
		else if (counter == 2) {
			nextCard->suit = 5;//clover
		}
		else {
			nextCard->suit = 6;//spades
		}

		//These assign a face to the card
		if (i == 14) {
			nextCard->face = 'A';
		}
		else if (i == 11) {
			nextCard->face = 'J';
		}
		else if (i == 12) {
			nextCard->face = 'Q';
		}
		else if (i == 13) {
			nextCard->face = 'K';
		}

		//resets i back to 2 for a new suit
		if ((i - 14 == 0) && (counter < 3)) {
			counter = counter + 1;
			i = 1; //will increment to 2 after loop ends
		}

		TailNode->next = nextCard;
		TailNode = nextCard;
	}

	TailNode->next = NULL; //last card in the deck points to nothing

	printf("Created: \n");
	PrintDeck(HeadNode, 4);
	ShuffleDeck(HeadNode, TailNode);
	printf("\nShuffled: \n");
	PrintDeck(HeadNode, 4);
	CreatePlayers(HeadNode);

}