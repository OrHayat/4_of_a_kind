#ifndef DECK_H_
#define DECK_H_

#include <iostream>
// constructing vectors
#include <vector>
#include "Card.h"


class Deck {
private:
	// Declare here the collection of "Card *" of the deck
    std::vector<Card*>* deck;
    int deck_size;
   
public:
    int deck_index;//index how many left
    Deck();
void push(Card* card);
    Deck& operator=(const Deck &other);
     void insert_FigCard(Figure f ,Shape s,int num=0);
    void insert_NumCard(int n,Shape s);
        Deck(std::vector<Card*>* deck,int max_Numeric=0);
	Card* fetchCard();   //Returns the top card of the deck and remove it from the deck
        int getNumberOfCards(); // Get the number of cards in the deck
	std::string toString(); // Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"
        ~Deck();//destrocur
        Deck(const Deck &other);
        Card* test(std::string);
    std::vector<Card*>& getVec()const ;
    int Get_Deck_Size()const;
};

#endif
