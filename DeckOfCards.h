/******************************
 **		DeckOfCards.h		 **
 **	Created by Charles Davis **
 **		CPSC 246-01			 **
 ******************************

  *************************************************************************** 
  *	DeckOfCards is a C++ Class that can be used to create a regular deck of *
  * of 52 cards for playing poker or for any other application that might   *
  * require a deck of playing cards.  It can also create and empty deck of  *
  * up to MAX number of cards.  In this case our MAX number is 52. It can   *
  * shuffle, cut, dealACard, accept a card along with a lot of other useful *
  * functions.																*
  *																			*	
  ***************************************************************************
  **		DeckOfCards()													   **
  ***************************************************************************
  **		Recieves: nothing												   **
  **		Returns:  nothing												   **
  **																		   **
  **		The default constructor for a deck of cards object.  It creates    **
  **		a new DeckOfCards with cards with 52 cards not shuffled. It also   **
  **		seeds a random number generator for shuffling. 					   **
  ***************************************************************************
  **		DeckOfCards(int n)												   **
  ***************************************************************************
  **		Receives: an integer n											   **
  **		Returns:  nothing												   **
  **																		   **	
  **		The alternate constructor for a deck of cards object.  It		   **
  **		creates a new DeckOfCards with n cards.  Currently it is not		   **
  **		implemented to be able to handle anthying but an empty deck of     **
  **		0 cards.  It also seed a random number generator for shuffling.	   **
  **	*************************************************************************
  **		void shuffle()													   **
  ***************************************************************************
  **		Receives: nothing												   **
  **		Returns:  nothing												   **
  **																		   **
  **		This function shuffles the deck of the instance from which it was  **
  **		called.  Leaving you with a randomized deck						   **
  **	*************************************************************************
  **		void cut()														   **
  ***************************************************************************
  **		Recieves: nothing												   **
  **		Returns:  nothing												   **
  **																		   **
  **		This function cuts the deck choosing a cutting point in the middle **
  **		third of the deck and swapping each section						   **
  **	*************************************************************************
  **		int DealACard()													   **
  ***************************************************************************
  **		Receives: nothing												   **
  **		Returns:  an int													   **
  **																		   **
  **		This function deals a card from the deck and reduces the number of **
  **		cards in the deck by 1. The card is returned as an integer from	   **
  **		0-51.															   **
  ***************************************************************************
  **		void acceptCard(int card)										   **
  ***************************************************************************
  **		Receives: an int													   **
  **		Returns:  nothing												   **
  **																		   **
  **		This function accepts a card with an integer value into the deck	   **
  **		and increase the deck size by 1.									   **
  ***************************************************************************
  **		bool isEmpty()													   **
  **	*************************************************************************
  **		Receives: nothing												   **
  **		Returns: a bool													   **
  **																		   **
  **		This function tests the deck to see if it still has cards left in  **
  **		it and returns to its caller true is the deck has no cards left    **
  **	*************************************************************************
  **		int getNumCards()												   **
  ***************************************************************************
  **		Receives: Nothing												   **
  **		Returns:  an int													   **
  **																		   **
  **		This function returns the number of cards left in the deck as an	   **
  **		integer bewtween 0-52.											   **
  ***************************************************************************
  **		void reset()														   **
  **	*************************************************************************
  **		Receives: nothing												   **
  **		Returns:  nothing												   **
  **																		   **
  **		This function resets the deck to its original order without		   **
  **		creating a new instance of the object.  Use this instead of		   **
  **		creating a new DeckOfCards to save memory and time.				   **
  ***************************************************************************
  **		void reset(bool empty)											   **
  ***************************************************************************
  **		Receives: a bool													   **
  **		Returns:  nothing												   **
  **																		   **
  **		This function resets the deck to an empty deck if the bool empty   **
  **		is true.	 And resets it to a regular 52 card deck if empty is false **
  ***************************************************************************
  **		void printDeck()													   **
  ***************************************************************************
  **		Receives: nothing												   **
  **		Returns:  nothing												   **
  **																		   **
  **		This function prints the entire deck with its cards string values  **
  **		(e.g. Ace of Clubs, Two of Hearts...)							   **
  ***************************************************************************
  **		int showCard(int cardIndex)										   **
  **	*************************************************************************
  **		Receives: an int													   **
  **		Returns:  an int													   **
  **																		   **
  **		This function shows a card to the user at the integer value		   **
  **		cardIndex without removing it.									   **
  ***************************************************************************
  **		string cardToString(int card)									   **
  ***************************************************************************
  **		Receives: an int													   **
  **		Returns:  a string												   **
  **																		   **
  **		This function accepts an integer card and returns its string value **
  **		(e.g. card 0 returns King of Clubs)								   **
  ***************************************************************************/


#ifndef DECK_OF_CARDS
#define DECK_OF_CARDS
#include <string>
using namespace std;


class DeckOfCards 
{
	public:
		DeckOfCards();
		DeckOfCards(int n);
		void shuffle();
		void cut();
		int dealACard();
		void acceptCard(int card);
		bool isEmpty();
		int getNumCards();
		void reset();
		void reset(bool empty);
		void printDeck();
		int showCard(int cardIndex);
		string cardToString(int card);

	private:
		static const int MAX = 52;
		int ary[MAX];
		int numCards;
};

#endif