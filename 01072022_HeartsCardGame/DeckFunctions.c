#include "Card.h"

/*Single card functions*/

//Return position from deck given card suit and num
int FindPositionFromCard(card* HeadNode, int suit, int num) {

	card* tempNode = HeadNode;
	int position = 0;

	for (int i = 1; i <= CountCards(HeadNode); ++i) {

		if ((tempNode->suit == suit) && (tempNode->num == num)) {

			position = i;
			break;

		}

		else if (i != CountCards(HeadNode)) {

			tempNode = tempNode->next;

		}

	}

	return position;
}

//Finds the suit of a card given position
char FindSuitFromPosition(card* HeadNode, int cardPosition) {

	card* temp = NULL;
	temp = (card*)malloc(sizeof(card));

	card* Target = HeadNode;

	//iterates until the user chosen card
	for (int i = 1; i < cardPosition; ++i) {

		Target = Target->next;

	}

	return Target->suit;
}

//Adds swapped card from HeadNode of PlayerN to tail of PlayerN+1 (used for when swapping three cards) //FIXME
card* ReturnNextPlayerTailNodeFromSwap(card* Player1HeadNode, int cardPosition, card* Player2TailNode, int init) {

	card* temp = NULL;
	temp = (card*)realloc(temp, sizeof(card));

	//card* Save = Deck;
	card* Target = Player1HeadNode;
	card* Prev = Player1HeadNode;

	//iterates until the user chosen card
	for (int i = 1; i < cardPosition; ++i) {

		Target = Target->next;

		if (i > 1) {

			//Save = Save->next;
			Prev = Prev->next;

		}

	}

	//Adds to the tail of the next player
	Player2TailNode->next = temp;
	Player2TailNode->next->face = Target->face;
	Player2TailNode->next->suit = Target->suit;
	Player2TailNode->next->num = Target->num;
	Player2TailNode = Player2TailNode->next;

	/*Points card before the target to the card after target (fixing gap in linked list):
		* if the target is not the first card
		* if the target is the first card and init is 1
	*/
	if ((cardPosition != CountCards(Player1HeadNode)) || (init == 1)) {

		Prev->next = Target->next;

	}

	//If the target is the first card, redefine HeadNode
	if (cardPosition == 1) {

		*Player1HeadNode = *Player1HeadNode->next;

	}

	return Player2TailNode;
}

//Function that looks for the major cards in the deck //ADDDETAILS
void FindBiggestAndSmallestCard(card* Bot, int* Heart, int* Diamond, int* Club, int* Spade, int* sHeart, int* sDiamond, int* sClub, int* sSpade, int* ValueH, int* ValueD, int* ValueC, int* ValueS, int* sValueH, int* sValueD, int* sValueC, int* sValueS) {

	int CardHeart = 0;
	int CardDiamond = 0;
	int CardClub = 0;
	int CardSpade = 0;

	int sCardHeart = 0;
	int sCardDiamond = 0;
	int sCardClub = 0;
	int sCardSpade = 0;

	card* BotClone = NULL;

	for (int suit = 3; suit <= 6; ++suit) {

		BotClone = Bot;

		for (int i = 1; i <= CountCards(Bot); ++i) {

			if ((BotClone->suit == 3) && (suit == 3)) {

				sCardHeart = i;
				*sValueH = BotClone->num;
				break;

			}

			else if ((BotClone->suit == 4) && (suit == 4)) {

				sCardDiamond = i;
				*sValueD = BotClone->num;
				break;

			}

			else if ((BotClone->suit == 5) && (suit == 5)) {

				sCardClub = i;
				*sValueC = BotClone->num;
				break;

			}

			else if ((BotClone->suit == 6) && (suit == 6)) {

				sCardSpade = i;
				*sValueS = BotClone->num;
				break;

			}

			if (i != CountCards(Bot)) {

				BotClone = BotClone->next;

			}

		}

	}


	for (int suit = 3; suit <= 6; ++suit) {

		BotClone = Bot;

		for (int i = 1; i <= CountCards(Bot); ++i) {

			if ((BotClone->suit == 3) && (suit == 3)) {

				CardHeart = i;
				*ValueH = BotClone->num;

			}

			else if ((BotClone->suit == 4) && (suit == 4)) {

				CardDiamond = i;
				*ValueD = BotClone->num;

			}

			else if ((BotClone->suit == 5) && (suit == 5)) {

				CardClub = i;
				*ValueC = BotClone->num;

			}

			else if ((BotClone->suit == 6) && (suit == 6)) {

				CardSpade = i;
				*ValueS = BotClone->num;

			}

			if (i != CountCards(Bot)) {

				BotClone = BotClone->next;

			}

		}

	}

	*Heart = CardHeart;
	*Diamond = CardDiamond;
	*Club = CardClub;
	*Spade = CardSpade;

	*sHeart = sCardHeart;
	*sDiamond = sCardDiamond;
	*sClub = sCardClub;
	*sSpade = sCardSpade;

}

//Finds the specified card //ADDDETAILS
int FindCard(card* Bot, card* Table, int Player, int HeartBroken, int starter, int tempwinner, int end, int suit, int tempwinnernum) {

	int Heart;
	int valueHeart = 0;
	int Diamond;
	int valueDiamond = 0;
	int Club;
	int valueClub = 0;
	int Spade;
	int valueSpade = 0;

	int sHeart;
	int svalueHeart = 0;
	int sDiamond;
	int svalueDiamond = 0;
	int sClub;
	int svalueClub = 0;
	int sSpade;
	int svalueSpade = 0;

	FindBiggestAndSmallestCard(Bot, &Heart, &Diamond, &Club, &Spade, &sHeart, &sDiamond, &sClub, &sSpade, &valueHeart, &valueDiamond, &valueClub, &valueSpade, &svalueHeart, &svalueDiamond, &svalueClub, &svalueSpade);

	//printf("%d %d %d %d %d %d %d %d", sHeart, Heart, sDiamond, Diamond, sClub, Club, sSpade, Spade);

	int Search = 0;
	int count = 1;
	int init = 0;
	int done = 0;
	card* pt1 = Bot;
	card* pt2 = Bot;
	int heartfound = 0; //specifies if there is a card of hearts on the table
	int QueenSpade = 0; //specifies if there is a queen of spades on the table
	card* TableClone = Table;

	//Checks to see if there is a card of hearts or Q spades on the table
	for (int i = 1; i <= 4; ++i) {

		if (TableClone == NULL) {

			break;

		}

		else if (TableClone->suit == 3) {

			heartfound = 1;

		}

		else if ((TableClone->suit == 6) && (TableClone->num == 12)) {

			QueenSpade = 1;

		}

		else if (TableClone->next != NULL) {

			TableClone = TableClone->next;

		}

	}

	//Iterate through the deck
	for (int i = 1; i <= CountCards(Bot); ++i) {

		if (Table == NULL) {

			break;

		}

		//If the person finding the card is not leading
		if (((starter != 0) && (end == 4)) || (end == 3)) {

			//if the suit by the player matches suit on the table
			if (pt1->suit == Table->suit) {

				Search = i;

				//only find the biggest value card of the leading suit if there are no penalty cards and the leading card is not a heart
				if ((Table->suit != 3) && (QueenSpade != 1) && (heartfound != 1) && (Player != 0)) {

					do {

						if (pt1->next == NULL) {

							break;

						}

						else {

							pt1 = pt1->next;

							if (pt1->suit == Table->suit) {

								Search = Search + 1;

							}

							if ((pt1->suit == Table->suit) && (pt1->suit == 6) && (pt1->num == 12) && (tempwinner != 0) && (pt1->next == NULL)) {

								if ((Search - 1) > i) {

									Search = Search - 1;

								}

								else {

									Search = i;

								}

							}

						}

					} while (pt1->next != NULL);

				}

				//if the queen is on the table or if there is a heart and a card of the suit is found we want to throw away the biggest value
				else if ((heartfound == 1) && (Player != 0)) {

					do {

						if (pt1->next == NULL) {

							break;

						}

						else {

							pt1 = pt1->next;

							if (pt1->num > tempwinnernum) {

								break;

							}

							else if (pt1->suit == Table->suit) {

								Search = Search + 1;

							}

						}

					} while (pt1->next != NULL);

				}

				break;
			}

			else {

				if (i != CountCards(Bot)) {

					pt1 = pt1->next;

				}

			}

		}


	}

	int found = 0;

	//If no cards with the suit are found
	if ((Search == 0) && (Player != 0)) {

		Search = 1;//first card in the deck, usually smallest heart

		//if the current winner is the player, we want to give the player the highest heart
		if (tempwinner == 0) {

			//if bot is not leading
			if (starter != 0) {

				if ((FindPositionFromCard(Bot, 6, 12) != 0) && ((tempwinnernum > 12) || (suit != 6))) {

					Search = FindPositionFromCard(Bot, 6, 12);

				}

				if (Heart != 0) {

					Search = Heart;

				}

			}

		}

		//if not, then we want to give away a big card of a non-heart suit, if statements allow for priority
		else {

			if ((valueDiamond >= valueClub) && (valueDiamond >= valueSpade) && (Diamond != 0)) { //if Daimond != 0

				Search = Diamond;
				found = 1;

			}

			if ((valueClub >= valueDiamond) && (valueClub >= valueSpade) && (Club != 0)) {

				Search = Club;
				found = 1;

			}

			//spade is priority but other cards  will be checked if the biggest card is Q Spades
			if ((valueSpade >= valueDiamond) && (valueSpade >= valueClub) && (Diamond != 0)) {

				if ((valueSpade != 12) && (Spade != 0)) {

					Search = Spade;
					found = 1;

				}

				else if (valueSpade == 12) {

					if ((valueDiamond >= valueClub) && (Diamond != 0)) {

						Search = Diamond;
						found = 1;

					}

					else if ((valueClub >= valueDiamond) && (Club != 0)) {

						Search = Club;
						found = 1;

					}

					else if ((svalueSpade != 12) && (svalueSpade != 0)) {

						Search = sSpade;
						found = 1;

					}

				}

			}

			//Sacrifice biggest heart if there is no other alternative
			else if ((Heart != 0) && (found == 0)) {

				Search = Heart;
				found = 1;

			}

			//If hearts has been broken the bot should play their smallest heart if it is less than 5
			if ((HeartBroken == 1) && (svalueHeart < 5) && (svalueHeart != 0) && (starter == 0)) {

				Search = sHeart;
				found = 1;

			}

		}

	}

	return Search;
}

//Checks entered value to make sure it is within the range //FIXME
int CheckValidNum(card* HeadNode, card* TailNode, int Card1, int Card2, int Card3, int numPlayer, card* Bot1, card* Bot2, card* Bot3, card* Bot1Tail, card* Bot2Tail, card* Bot3Tail) {

	int valid = 1;

	if ((Card1 < 1) || (Card2 < 1) || (Card3 < 1)) {

		valid = 0;
		printf("Card number must be greater than 0\n");

	}

	if ((Card1 > numPlayer) || (Card2 > numPlayer) || (Card3 > numPlayer)) {

		valid = 0;
		printf("Card number must be less than or equal to %d\n", numPlayer);

	}

	if ((Card1 == Card2) || (Card2 == Card3) || (Card1 == Card3)) {

		valid = 0;
		printf("All three numbers must be different\n");

	}

	//Swaps The Cards To The Next Player
	if (valid == 1) {

		//Organizes the three cards so the biggest card is first
		int max[3] = { Card1, Card2, Card3 };

		for (int i = 0; i < 3; ++i) {

			for (int j = 0; j < 2; ++j) {

				if (max[j] < max[j + 1]) {

					int temp;
					temp = max[j];
					max[j] = max[j + 1];
					max[j + 1] = temp;

				}

			}

		}

		int Heart3;
		int valueHeart3 = 0;
		int Diamond3;
		int valueDiamond3 = 0;
		int Club3;
		int valueClub3 = 0;
		int Spade3;
		int valueSpade3 = 0;

		int sHeart3;
		int svalueHeart3 = 0;
		int sDiamond3;
		int svalueDiamond3 = 0;
		int sClub3;
		int svalueClub3 = 0;
		int sSpade3;
		int svalueSpade3 = 0;

		FindBiggestAndSmallestCard(Bot3, &Heart3, &Diamond3, &Club3, &Spade3, &sHeart3, &sDiamond3, &sClub3, &sSpade3, &valueHeart3, &valueDiamond3, &valueClub3, &valueSpade3, &svalueHeart3, &svalueDiamond3, &svalueClub3, &svalueSpade3);

		int Bot3Card1 = max[0];
		int Bot3Card2 = max[1];
		int Bot3Card3 = max[2];

		//Give away hearts greater than J
		if ((FindPositionFromCard(Bot3, 3, 14) != 0) && (FindPositionFromCard(Bot3, 3, 14) != max[0]) && (FindPositionFromCard(Bot3, 3, 14) != max[1]) && (FindPositionFromCard(Bot3, 3, 14) != max[2])) {

			Bot3Card1 = FindPositionFromCard(Bot3, 3, 14);

		}

		if ((FindPositionFromCard(Bot3, 3, 13) != 0) && (FindPositionFromCard(Bot3, 3, 13) != max[0]) && (FindPositionFromCard(Bot3, 3, 13) != max[1]) && (FindPositionFromCard(Bot3, 3, 13) != max[2])) {

			Bot3Card2 = FindPositionFromCard(Bot3, 3, 13);

		}

		if ((FindPositionFromCard(Bot3, 3, 12) != 0) && (FindPositionFromCard(Bot3, 3, 12) != max[0]) && (FindPositionFromCard(Bot3, 3, 12) != max[1]) && (FindPositionFromCard(Bot3, 3, 12) != max[2])) {

			Bot3Card3 = FindPositionFromCard(Bot3, 3, 12);

		}

		//Give away spades greater than J
		if ((FindPositionFromCard(Bot3, 6, 14) != 0) && (FindPositionFromCard(Bot3, 6, 14) != max[0]) && (FindPositionFromCard(Bot3, 6, 14) != max[1]) && (FindPositionFromCard(Bot3, 6, 14) != max[2])) {

			Bot3Card1 = FindPositionFromCard(Bot3, 6, 14);

		}

		if ((FindPositionFromCard(Bot3, 6, 13) != 0) && (FindPositionFromCard(Bot3, 6, 13) != max[0]) && (FindPositionFromCard(Bot3, 6, 13) != max[1]) && (FindPositionFromCard(Bot3, 6, 13) != max[2])) {

			Bot3Card2 = FindPositionFromCard(Bot3, 6, 13);

		}

		if ((FindPositionFromCard(Bot3, 6, 12) != 0) && (FindPositionFromCard(Bot3, 6, 12) != max[0]) && (FindPositionFromCard(Bot3, 6, 12) != max[1]) && (FindPositionFromCard(Bot3, 6, 12) != max[2])) {

			Bot3Card3 = FindPositionFromCard(Bot3, 6, 12);

		}

		//Give away 2 of Clubs
		if ((svalueClub3 == 2) && (sClub3 != max[0]) && (sClub3 != max[1]) && (sClub3 != max[2])) {

			Bot3Card1 = sClub3;

		}

		Bot1Tail = ReturnNextPlayerTailNodeFromSwap(HeadNode, max[0], Bot1Tail, 0);
		Bot1Tail = ReturnNextPlayerTailNodeFromSwap(HeadNode, max[1], Bot1Tail, 0);
		Bot1Tail = ReturnNextPlayerTailNodeFromSwap(HeadNode, max[2], Bot1Tail, 0);
		Bot1Tail->next = NULL;

		//Redefining Tail if the 13th card is chosen to be swapped
		if ((Card1 == 13) || (Card2 == 13) || (Card3 == 13)) {

			card* temp = NULL;
			temp = HeadNode;

			for (int i = 0; i < 9; ++i) {

				temp = temp->next;
				TailNode = temp;

			}

		}

		Bot2Tail = ReturnNextPlayerTailNodeFromSwap(Bot1, max[0], Bot2Tail, 1);
		Bot2Tail = ReturnNextPlayerTailNodeFromSwap(Bot1, max[1], Bot2Tail, 1);
		Bot2Tail = ReturnNextPlayerTailNodeFromSwap(Bot1, max[2], Bot2Tail, 1);
		Bot2Tail->next = NULL;

		Bot3Tail = ReturnNextPlayerTailNodeFromSwap(Bot2, max[0], Bot3Tail, 1);
		Bot3Tail = ReturnNextPlayerTailNodeFromSwap(Bot2, max[1], Bot3Tail, 1);
		Bot3Tail = ReturnNextPlayerTailNodeFromSwap(Bot2, max[2], Bot3Tail, 1);
		Bot3Tail->next = NULL;

		TailNode = ReturnNextPlayerTailNodeFromSwap(Bot3, Bot3Card1, TailNode, 1);
		TailNode = ReturnNextPlayerTailNodeFromSwap(Bot3, Bot3Card2, TailNode, 1);
		TailNode = ReturnNextPlayerTailNodeFromSwap(Bot3, Bot3Card3, TailNode, 1);
		TailNode->next = NULL;

	}

	return valid;
}


/*Full deck functions*/

//Card Counting Function
int CountCards(card* HeadNode) {
	int num = 0;
	while (HeadNode != NULL) {
		num = num + 1;
		HeadNode = HeadNode->next;
	}
	return num;
}

//Card Sorting Function (EC+)
void SortCards(card* HeadNode, int numCards) {

	card* Swap;
	Swap = (card*)malloc(sizeof(card));

	//If there are more than 1 card in the node, then we can swap cards
	if (numCards > 1) {

		for (int i = numCards; i > 0; --i) {

			card* First = HeadNode;
			card* Second = HeadNode->next;

			for (int j = numCards; j > 0; --j) {

				//Suit arrangement
				if (Second->suit < First->suit) {

					Swap->face = First->face;
					Swap->num = First->num;
					Swap->suit = First->suit;

					First->face = Second->face;
					First->num = Second->num;
					First->suit = Second->suit;

					Second->face = Swap->face;
					Second->num = Swap->num;
					Second->suit = Swap->suit;

				}

				//Number arrangement for like suits
				if ((Second->num < First->num) && (Second->suit == First->suit)) {

					Swap->face = First->face;
					Swap->num = First->num;
					Swap->suit = First->suit;

					First->face = Second->face;
					First->num = Second->num;
					First->suit = Second->suit;

					Second->face = Swap->face;
					Second->num = Swap->num;
					Second->suit = Swap->suit;

				}

				//Breaks the first loop if there is no card after the second card
				if (Second->next == NULL) {

					break;

				}

				//Iterates through the linked list
				else {

					First = First->next;
					Second = Second->next;

				}

			}
		}
	}
}

//Shuffling Deck Function
void ShuffleDeck(card* HeadNode, card* TailNode) {

	//Iterates 500 times to make sure everything is shuffled
	for (int i = 0; i < 500; ++i) {

		int num1 = rand() % 52;
		int num2 = rand() % 52;
		card* Card1 = HeadNode;
		card* Card2 = HeadNode;
		card* Swap = NULL;
		Swap = (card*)(malloc(sizeof(card)));

		for (int i = 1; i < num1; i++) {

			Card1 = Card1->next;

		}

		for (int j = 1; j < num2; j++) {

			Card2 = Card2->next;

		}

		Swap->face = Card1->face;
		Swap->num = Card1->num;
		Swap->suit = Card1->suit;

		Card1->face = Card2->face;
		Card1->num = Card2->num;
		Card1->suit = Card2->suit;

		Card2->face = Swap->face;
		Card2->num = Swap->num;
		Card2->suit = Swap->suit;

	}

}