/*************************************************
 **		Poker Hand Probability Simulation		**
 **			Created By Charles Davis				**
 **			CPSC 246-01 Dr. Valentine			**
 *************************************************/

/*	Poker Hand Probability Simulation uses a DeckOfCards to deal poker hands
 *  to test for the probability of the occurence of a test hand in a game of 
 *  five card stud.  It will start with the minimum number of hands and test 
 *  each hand to check for the given poker hand to be tested.  Each iteration 
 *	after it doubles the number of hands until it reaches the maximum number of 
 *  hands listed in the constants section of the variables. Finally it returns
 *  the probability for each iteration and returns an average of the	 trial.  
 *  This sim can run using a fresh deck for each hand indicated by a bool
 *  or it can also deal most of the cards to a given number of players. 
 *  I started it with 8 players because it is a multiple of 64 which is the 
 *  minimum and it is also a power of 2.  This version of the program also 
 *  outputs the results to 2 seperate text files one for a fresh deck and
 *  the other for a deck that has had most of its cards dealt in "games" as if
 *  it were a 8 guys at a poker table.
 */



#include "DeckOfCards.h"		//must include to create DeckOfCards objects
#include <iostream>
#include <fstream>			//included for writing to file
#include <string>
using namespace std;

const int NUM_PLAYERS = 8;		//to run trials where most of the deck is dealt
const int CARDS_IN_HAND = 5;		//5 card stud
const int CARDS_IN_SUIT = 13;	
const int MIN_NUM_HANDS = 64;			//start trial with
const int MAX_NUM_OF_HANDS = 2097512;	//end trial when
const int NUM_TRIALS = 1;


//this is enum class is used to be able to test for different types of hands
enum PokerHand 
	{PAIR, TWO_PAIR, THREE_OF_A_KIND, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND };


//function prototypes
bool hasAFullHouse(DeckOfCards hand);
bool hasAPair(DeckOfCards hand);
bool hasTwoPair(DeckOfCards hand);
bool hasThreeOfAKind(DeckOfCards hand);
bool hasFourOfAKind(DeckOfCards hand);
bool hasAFlush(DeckOfCards hand);

double doSim(int maxNumHands, int testType, bool freshDeck, ofstream& output);
double getPercentage(int totalHands, int handType,  bool freshDeck);

void init();



/****************************** Main ******************************/
int main ()
{
	//Variable Dictionary
	double averageOdds;		//average odds of the current trial
	ofstream output;			//ouput stream for writing data to file

	//1.0 Init
	init();		//prints name, class and assignment name

	//Open a file for the fresh deck trial results and set it to append
	output.open("Fresh.txt", ios::app);

	//2.0a process with a fresh deck
	for(int i = 0; i < NUM_TRIALS; i++)
	{
		//write to file the current trial number
		output << "\nTrial " << i << "\n" << endl;

		//get the average odds of the trial by doing the simulation
		averageOdds = doSim(MAX_NUM_OF_HANDS, FULL_HOUSE, true, output);

		//print to the console the average odds
		cout << "\n\nThe average odds of the sim are " << averageOdds << endl;
	}
	
	//3.0a output: close and save file with results
	output.close();


	//open a file for the not fresh deck trial results and set it to append
	output.open("notFresh.txt", ios::app);
	
	//2.0b process dealing most of the deck each trial
	for(int i = 0; i < NUM_TRIALS; i++)
	{
		//write to file the current trial number
		output << "\nTrial " << i << "\n" << endl;

		//get the average odds of the trial by doing the simulation
		averageOdds = doSim(MAX_NUM_OF_HANDS, FULL_HOUSE, false, output);

		//print to the console the average odds
		cout << "\n\nThe average odds of the sim are " << averageOdds << endl;
	}

	//3.0b output: close and save file with results
	output.close();

	//program run was successful print out and return 0
	cout << "\n\n\n\t Normal Termination \n\n\n" << endl;

	return 0;
}



/****************************** Init *******************************/
void init()
{
	cout << "\n\n====================================================" << endl;
	cout << "   Charles Davis - CPSC 246.01 - Poker Hand Sim" << endl;
	cout << "====================================================\n\n" << endl;
}



/***************************** doSim *******************************/
double doSim(int maxNumHands, int testType, bool freshDeck, ofstream& output)
{
	// recieves the maximum number of hands, the type of hand to be tested,
	// and a bool indicating whether or not to use a fresh deck.  As well
	// as the output stream for file writing.  The simulation runs from 
	// MIN_NUM_HANDS to maxNumHands counting the number of occurences of the 
	// hand type being tested.  It writes out to file the results of each trial
	// and the final average of the entire trial.  Then it returns the trial
	// average to its caller as a double

	
	double cycleCounter = 0.0, currentOdds = 0.0, averageOdds = 0.0;
	string handType;

	// this switch block is for creating a meaningful string based on the hand
	// type being tested. 

	switch(testType)
	{
        case PAIR:				handType = "pair";				break;
        case TWO_PAIR:			handType = "two pair";			break;
        case THREE_OF_A_KIND:	handType = "three of a kind";	break;
        case FLUSH:				handType = "flush";				break;
        case FULL_HOUSE:			handType = "full house";			break;
        case FOUR_OF_A_KIND:		handType = "four of a kind";		break;
        default:													break;	
	}
		//output to file and console
		output << "\n\nThe odds of " << handType << " are: \n\n" << endl;
		cout << "\n\nThe odds of " << handType << " are: \n\n" << endl;	


	// starting with the minimum number of hands doubling up to maxNumHands
	for (int i = MIN_NUM_HANDS; i <= maxNumHands; i += i)
	{ 
		// get the odds of currentNumhands of the hand being tested
		// with a fresh deck or not.  

		currentOdds = getPercentage(i, testType, freshDeck);
		cout << "For " << i << " hands tested " << currentOdds << endl;

		cycleCounter++;		//count number of cycles of the trial for average
		averageOdds += currentOdds;

		output << i << " " << currentOdds << "\n" << endl; 
	}

	// calulate the trial average odds by dividing by the number of cycles
	averageOdds = averageOdds / cycleCounter;

	// write the average odds of the trial to file
	output << "Average odds are " << averageOdds << "\n" << endl;

	// and also return it to the caller
	return averageOdds;
}




/************************* getPercentage **************************/
double getPercentage(int totalHands, int handType, bool freshDeck)
{
		
		// var that counts the number of hands of the handType being tested
		int countHands = 0;	
							
		DeckOfCards myDeck;		// deck of cards to be dealt from
		DeckOfCards hand;		// empty deck that is a hand
		DeckOfCards hands[NUM_PLAYERS];	 //array of hands for not fresh deck


		if(freshDeck)	//if the caller wants a fresh deck each time
		{

			// for the number of total hands in the trial
			for (int i = 0; i < totalHands; i++)
			{

				myDeck.reset();		//reset the deck to unshuffled
				myDeck.shuffle();	//shuffle it a few times just to be safe
				myDeck.shuffle();
				myDeck.shuffle();
				myDeck.cut();		// cut it just to be safer

				hand.reset(true);	// reset the player hand to an empty hand
	

				// deal the hand to the empty hand that is a deck
				for(int card = 0; card < CARDS_IN_HAND; card++)
				{
					hand.acceptCard(myDeck.dealACard());		//deal card to hand
				}

				
				// depending on hand type we check to see if the case is true
				// and it counts the hands found
				switch(handType)
					{
                        case PAIR:
                            if(hasAPair(hand))
								countHands++;	break;
                        case TWO_PAIR:
                            if(hasTwoPair(hand))
								countHands++;	break;
                        case THREE_OF_A_KIND:
                            if(hasThreeOfAKind(hand))
								countHands++;	break;
                        case FLUSH:
                            if(hasAFlush(hand))
								countHands++;	break;
                        case FULL_HOUSE:
                            if(hasAFullHouse(hand))
								countHands++;	break;
                        case FOUR_OF_A_KIND:
                            if(hasFourOfAKind(hand))
								countHands++;	break;
                        default:
                            break;	
					} // end switch

			}// end trial of totalHands

		} // end fresh deck
		else		//if it is not a fresh deck
		{
			// we deal hands to an array of NUM_PLAYERS

			for (int i = 0; i < (totalHands / NUM_PLAYERS); i++)
			{

				myDeck.reset();		// reset the deck each "game" or "round"
				myDeck.shuffle();	// shuffle a few times
				myDeck.shuffle();
				myDeck.shuffle();
				myDeck.cut();		// cut to be safe


				// we reset the hands each trial to be empty hands
				for(int i = 0; i < NUM_PLAYERS; i++)
				{
					hands[i].reset(true);
				}

				// we deal as many hands as there are players
				for(int card = 0; card < CARDS_IN_HAND; card++)
				{
					for(int player = 0; player < NUM_PLAYERS; player++)
					{
						hands[player].acceptCard(myDeck.dealACard());
					}
				}

				// depending on the handType being tested we check to see
				// if handType exists and we increment the counter if it does
				for(int player = 0; player < NUM_PLAYERS; player++)
				{
					switch(handType)
					{
                        case PAIR:
                            if(hasAPair(hands[player]))
								countHands++;	break;
                        case TWO_PAIR:
                            if(hasTwoPair(hands[player]))
								countHands++;	break;
                        case THREE_OF_A_KIND:
                            if(hasThreeOfAKind(hands[player]))
								countHands++;	break;
                        case FLUSH:
                            if(hasAFlush(hands[player]))
								countHands++;	break;
                        case FULL_HOUSE:
                            if(hasAFullHouse(hands[player]))
								countHands++;	break;
                        case FOUR_OF_A_KIND:
                            if(hasFourOfAKind(hands[player]))
								countHands++;	break;
                        default:
                            break;	
					} //end switch
				} // end for each player
			} // end for each game or round
		} // end if not fresh deck

		// return the percentage of hands found to total hands
		return (double)countHands / (double)totalHands;

} // end getPercentage



/************************* hasAFullHouse *************************/
bool hasAFullHouse(DeckOfCards hand)
{
	// using a temporary array of size CARDS_IN_SUIT this function goes through
	// the hand sent to it and increments the count of each position 
	// in the array that has the card type being searched for and returns
	// true if the hand is found based on the logic of the hand type being
	// tested for.

	int tempArray[CARDS_IN_SUIT];
	bool pair = false;		// testing for pair
	bool triple = false;		// testing for triple

	// init our temp array
	for(int index = 0; index < CARDS_IN_SUIT; index++){
		tempArray[index] = 0;
	}

	// for each card in the hand increment the count of the cards found
	for(int i = 0; i < CARDS_IN_HAND; i++)
	{
		// look at the current card and find its value
		// goto the index in the array of the value of the card
		// and increment it

		tempArray[hand.showCard(i) % CARDS_IN_SUIT]++;
	}
		
		
	// for each elemnt in temp array check to see if the value was incremented
	for(int j = 0; j < CARDS_IN_SUIT; j++)
	{
		if(tempArray[j] == 2)		// if temp array has a 2 that means we
		{							// found a pair. Set pair to be true
			pair = true;
		}else if(tempArray[j] == 3)	// if temp array has a 3 that means we
		{							// found a triple. Set triple to true
			triple = true;
		}else {}
	}

	if(pair && triple)				// if we have a pair and a triple its a							
		return true;					// full house so return true

	// else not a full house
	return false;

} // end full house



/************************** hasAPair ******************************/
bool hasAPair(DeckOfCards hand)
{
	// using a temporary array of size CARDS_IN_SUIT this function goes through
	// the hand sent to it and increments the count of each position 
	// in the array that has the card type being searched for and returns
	// true if the hand is found based on the logic of the hand type being
	// tested for.

	int tempArray[CARDS_IN_SUIT];
	bool pair = false; 

	// init temp array
	for(int index = 0; index < CARDS_IN_SUIT; index++)
	{
		tempArray[index] = 0;
	}

	// for each card in the hand increment the count of the cards found
	for(int i = 0; i < CARDS_IN_HAND; i++)
	{
		// look at the current card and find its value
		// goto the index in the array of the value of the card
		// and increment it

		tempArray[hand.showCard(i) % CARDS_IN_SUIT]++;
	}
	
	// for each elemnt in temp array check to see if the value was incremented
	for(int j = 0; j < CARDS_IN_SUIT; j++)
	{
		// if temp array has a 2, 3, or 4 that means it is at least a pair
		// set pair to true
		if(tempArray[j] == 2 || tempArray[j] == 3 || tempArray[j] == 4)
			pair = true;
	}

	if(pair)
		return true;

	// else not a pair
	return false;

} // and pair



/************************** hasTwoPair *****************************/
bool hasTwoPair(DeckOfCards hand)
{
	// using a temporary array of size CARDS_IN_SUIT this function goes through
	// the hand sent to it and increments the count of each position 
	// in the array that has the card type being searched for and returns
	// true if the hand is found based on the logic of the hand type being
	// tested for.

	//will not return true if three or four of a kind

	int pairCounter = 0;		// this var counts the number of pairs

	int tempArray[CARDS_IN_SUIT];
	bool pair = false; 
	
	// init temp array
	for(int index = 0; index < CARDS_IN_SUIT; index++)
	{
		tempArray[index] = 0;
	}

	// for each card in the hand increment the count of the cards found
	for(int i = 0; i < CARDS_IN_HAND; i++)
	{
		// look at the current card and find its value
		// goto the index in the array of the value of the card
		// and increment it

		tempArray[hand.showCard(i) % CARDS_IN_SUIT]++;
	}
	
	// for each element in the temp array check to see if it has a pair
	for(int j = 0; j < CARDS_IN_SUIT; j++)
	{
		if(tempArray[j] == 2) // if it has a pair increment the pair counter
			pairCounter++;
	}

	if(pairCounter == 2)		// if it is two pairs exactly and not 4 of a kind
		return true;

	// else not 2 pairs
	return false;

} // end two pair



/*********************** hasThreeOfAKind **************************/
bool hasThreeOfAKind(DeckOfCards hand)
{
	// using a temporary array of size CARDS_IN_SUIT this function goes through
	// the hand sent to it and increments the count of each position 
	// in the array that has the card type being searched for and returns
	// true if the hand is found based on the logic of the hand type being
	// tested for.

	int tempArray[CARDS_IN_SUIT];
	bool triple = false; 

	//init temp array
	for(int index = 0; index < CARDS_IN_SUIT; index++)
	{
		tempArray[index] = 0;
	}

	// for each card in the hand increment the count of the cards found
	for(int i = 0; i < CARDS_IN_HAND; i++)
	{
		// look at the current card and find its value
		// goto the index in the array of the value of the card
		// and increment it

		tempArray[hand.showCard(i) % CARDS_IN_SUIT]++;
	}
	

	// for each element in temp array check to see if it is at least a triple
	for(int j = 0; j < CARDS_IN_SUIT; j++)
	{
		// if it is 3 or 4 triple is true
		if(tempArray[j] == 3 || tempArray[j] == 4) 
			triple = true;
	}

	if(triple)		// if it is a triple return true
		return true;

	// else it is not three of a kind
	return false;

} // end has three of a kind



/*********************** hasFourOfAKind ***************************/
bool hasFourOfAKind(DeckOfCards hand)
{
	// using a temporary array of size CARDS_IN_SUIT this function goes through
	// the hand sent to it and increments the count of each position 
	// in the array that has the card type being searched for and returns
	// true if the hand is found based on the logic of the hand type being
	// tested for.

	int tempArray[CARDS_IN_SUIT];
	bool quad = false; 


	// init temp array
	for(int index = 0; index < CARDS_IN_SUIT; index++)
	{
		tempArray[index] = 0;
	}

	// for each card in the hand increment the count of the cards found
	for(int i = 0; i < CARDS_IN_HAND; i++)
	{
		// look at the current card and find its value
		// goto the index in the array of the value of the card
		// and increment it

		tempArray[hand.showCard(i) % CARDS_IN_SUIT]++;
	}
	
	// for each element in temp array check to see if it is a quad
	for(int j = 0; j < CARDS_IN_SUIT; j++)
	{
		if(tempArray[j] == 4)	// if temp array has a 4 quad is true
			quad = true;
	}

	if(quad)		// if it is a quad return true
		return true;

	//else it is not a quad
	return false;

} // end has four of a kind



/************************* hasAFlush ******************************/
bool hasAFlush(DeckOfCards hand)
{
	// using a temporary array of size CARDS_IN_HAND this function goes through
	// the hand sent to it and increments the count of each position 
	// in the array that has the card type being searched for and returns
	// true if the hand is found based on the logic of the hand type being
	// tested for.

	int tempArray[CARDS_IN_HAND];
	bool flush = false;

	// init temp array
	for(int index = 0; index < CARDS_IN_HAND; index++)
	{
		tempArray[index] = 0;
	}

	// for each card in the hand increment the count of the cards found
	for(int i = 0; i < CARDS_IN_HAND; i++)
	{
		// look at the current card and find its value
		// goto the index in the array of the value of the card
		// and increment it

		tempArray[hand.showCard(i) / CARDS_IN_SUIT]++;
	}

	// for each element in temp array check to see if the element is a flush
	for(int j = 0; j < CARDS_IN_HAND; j++)
	{
		if(tempArray[j] == CARDS_IN_HAND)	// if all of cards have the same
			flush = true;					// suit then temp array will equal 
	}										// cards in hand. Set flush to true

	if(flush)	// if its a flush return true
		return true;

	// else not a flush
	return false;
}