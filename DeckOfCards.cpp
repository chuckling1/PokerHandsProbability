/******************************
 **		DeckOfCards.cpp		 **
 **	Created by Charles Davis **
 **		CPSC 246-01			 **
 ******************************

 ***************************************************************************
 **	DeckOfCards.cpp is the implemtation file for the DeckOfCards class    **
 ** Since a deck of cards is in this case just an array of integers we	  **
 ** had to make some special cases for the face value of the cards.		  **
 **																		  **
 ** If we take the int value of the card from 0-51 and mod it by 13 we	  **
 ** get the face value of the card and if we divide that same integer by  **
 ** 13 it will give use the suit value of the card						  **
 **																		  **
 **		FACE VALUE = int card % 13		SUIT VALUE = int card / 13		  **
 **																		  **
 **	Based on this logic we can assign special values to a few cards in	  **
 ** the deck and special values to the suits of the cards				  **
 **																		  **
 **		KING = 0		ACE = 1	   "2-10" = 2-10	    JACK = 11	QUEEN = 12	  **
 **																		  **
 **		CLUBS = 0		DIAMONS = 1		HEARTS = 2		SPADES = 3		  **
 **																		  **
 ** See the cardToString function for further clarification on this code  **
 ** Everything else is explained clearly in the rest of the file.		  **
 **																		  **
 **				Good Luck and have fun playing card games!				  **
 ***************************************************************************/



#include <iostream>
#include <string>
#include "DeckOfCards.h"
#include "time.h"
using namespace std;



/*************************** DeckOfCards default ****************************/
DeckOfCards::DeckOfCards()
	{
		//	The default constructor for a deck of cards object.  It creates  
  		//	a new DeckOfCards with cards with 52 cards not shuffled. It also   
		//	seeds a random number generator for shuffling.

		srand((unsigned) time(0));	// Seed a random number generator
									// based on the time
		numCards = MAX;				// set the maximum deck size

		for(int i = 0; i < MAX; i++) //init the array from 0-51
		{
			ary[i] = i;
		}
	}//end constructor



/*************************** DeckOfCards alternate ***************************/
DeckOfCards::DeckOfCards(int n)
	{
		// The alternate constructor for a deck of cards object.  It		   
 		// creates a new DeckOfCards with n cards.  Currently it is not		   
  		// implemented to be able to handle anthying but an empty deck of  
  		// 0 cards.  It also seed a random number generator for shuffling.

		srand((unsigned) time(0));	// Seed a random number generator 
		if(n==0)						// based on the time
		{
			numCards = 0;			// make an empty hand with zero cards
		}else
		{
			cerr << "This function hasn't been developed yet. " << endl;
			cerr << "Creating a deck with 0 cards..." << endl;
			numCards = 0;
		}
	} //end constructor 2



/********************************* shuffle ***********************************/
void DeckOfCards::shuffle()
	{
		// shuffle creates two random numbers to be used as array indices
		// and swaps them in the array.  It does this 1,000 times to
		// randomize well.

		int randomIndex1, randomIndex2;
		int temp;


		for(int i = 0; i < 1000; i++)	//swap random indicies 1,000 times
		{
			randomIndex1 = rand() % MAX;		// get 1st random from 0 to MAX
			randomIndex2 = rand() % MAX;		// get 2nd random from 0 to MAX
			
			temp = ary[randomIndex1];				// swap them
			ary[randomIndex1] = ary[randomIndex2];
			ary[randomIndex2] = temp;
		}
	} // end shuffle



/*********************************** cut *************************************/
void DeckOfCards::cut()
	{
		// cut creates two partitions of the deck array using a cut point 
		// within the middle third of the deck and swaps them.

		int tempAry[MAX];
		int oneThird, twoThirds, cutPoint;
		int loc = 0;			// temp var to indicate the current index in array

		oneThird = numCards / 3;			// find the first 3rd
		twoThirds = (numCards * 2) / 3;	// find the second third

		cutPoint = (rand()%((twoThirds-oneThird)+1)); // find a cut point
		cutPoint += oneThird;						  // within the middle 3rd
													  // and add the bottom 3rd
		
		for(int i = cutPoint; i < numCards; i++)		// take the top and add
		{											// it to the temp array
			tempAry[loc] = ary[i];
			loc++;					// increment the location in temp array
		}

		for(int i = 0; i < cutPoint; i++)	// start from location in temp ary
		{
			tempAry[loc] = ary[i];		// get the bottom partition
			loc++;						// and add it to the temp array 
		}								// from the temp location to cut point

		for(int i = 0; i < numCards; i++)	// copy temp array back to original
		{
			ary[i] = tempAry[i];
		}
	} // end cut



/******************************* dealACard ***********************************/
int DeckOfCards::dealACard()
	{
		// deals a card from the top of the array and decrements the number of 
		// cards in the deck

		int tempCard = ary[numCards-1];		// from the top get a int card
		numCards--;							// decrement the num cards in deck
		return tempCard;						// return the card to caller
	}



/******************************* acceptCard **********************************/
void DeckOfCards::acceptCard(int card)
	{
		// accepts an integer card and adds it to the deck if the 
		// deck is not full and then increments the number of cards

		// if the card is not negative and is within range of MAX
		if(card >= 0 && card < MAX)	
		{								
			if(numCards < MAX)	// and there is room in the deck
			{
				ary[numCards] = card;	// add a card to the top of the deck
				numCards++;				// increment the number of cards
			}
			else		// the deck is full
			{
				cerr << "Sorry the deck is full, cannot add card" << endl;
			}
		}
		else		// invalid card value
		{
			cerr << "Sorry the card value you added is not within valid range" << endl;
		}
	}	// end acceptCard



/******************************* isEmpty *************************************/
bool DeckOfCards::isEmpty()
	{
		// returns true if the deck is empty

		if(numCards > 0)
			return false;	
		
		else
			return true;
	}



/****************************** getNumCards **********************************/
int DeckOfCards::getNumCards()
	{
		// returns the current number of cards in the deck
		return numCards;
	}



/********************************* reset *************************************/
void DeckOfCards::reset()
	{
		// resets the deck to the original deck of MAX cards and puts them
		// into the original order 0-51

		numCards = MAX;
		for(int i = 0; i < MAX; i++)
		{
			ary[i] = i;
		}
	}



/******************************** reset empty ********************************/
void DeckOfCards::reset(bool empty)
{		
		// if empty is true it resets an empty deck to its original 
		// empty state with 0 cards otherwise it resets the deck to a fresh
		// MAX sized deck by calling the other reset function
			
		if(empty)
			numCards = 0;
		else
			reset();
}



/******************************** printDeck **********************************/
void DeckOfCards::printDeck()
	{	
		// prints the current deck out by calling the cardToString function
		// for each element in the current deck array

		cout << endl;

		for(int i = numCards-1; i >= 0; i--)		// from the top of the deck
		{
			// print out the string version of the card at index i;
			cout << cardToString(ary[i]) << "  " << endl;

			// every 13 cards start a new row
			if((i % 13) == 0)
			{
				cout << endl;
			}
		}
	}



/******************************* cardToString ********************************/
string DeckOfCards::cardToString(int card)
	{
		// returns the string value of a card's integer value by dividing and 
		// modding the integer value to get the suit and face value of the card

		string strValue = " ";	// temp string to be concatonated for result
		int cardValue = card % 13;	// get face value
		int cardSuit = card / 13;	// get card suit

		switch (cardValue)	// depending on the face value get string value
		{					// add the string value to the temp string
			case 0:	 strValue += "King of ";		break;
			case 1:  strValue += "Ace of ";		break;
			case 2:  strValue += "Two of ";		break;
			case 3:  strValue += "Three of ";	break;
			case 4:  strValue += "Four of ";		break;
			case 5:  strValue += "Five of ";		break;
			case 6:  strValue += "Six of ";		break;
			case 7:  strValue += "Seven of ";	break;
			case 8:  strValue += "Eight of ";	break;
			case 9:  strValue += "Nine of ";		break;
			case 10: strValue += "Ten of " ;		break;
			case 11: strValue += "Jack of ";		break;
			case 12: strValue += "Queen of ";	break;
			default: strValue += "Invalid ";		break;
		}

		switch (cardSuit)	// depending on the suit get string suit
		{					// append the suit string to the temp string
			case 0:  strValue += "Clubs\n\n";		break;
			case 1:  strValue += "Diamonds\n\n";		break;
			case 2:  strValue += "Hearts\n\n";		break;
			case 3:  strValue += "Spades\n\n";		break;
			default: strValue += "Invalid ";			break;
		}

		// return the final resulting string value of the int card
		return strValue;

	} // end cardToString



/********************************** showCard *********************************/
int DeckOfCards::showCard(int cardIndex)
{
	// shows the card to the user without dealing and destroying the deck
	// useful for checking hand types in poker

	return ary[cardIndex];
}