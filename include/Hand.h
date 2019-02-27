#ifndef HAND_H_
#define HAND_H_
#include <vector>

#include <iostream>

#include "Card.h"

class Hand {
private:
        std::vector<Card*>* hand_cards;
public:
    Hand(int N);
    void remove_4(Card &card);
    bool search(Card &card);
    Hand(const Hand &other);
    unsigned int num_cards;//N
    bool addCard(Card &card);
    bool removeCard(Card &card);
    Hand& operator=(const Hand &other);
    int GetNumberOfCards(); // Get the number of cards in hand
    std::string toString(); // Return a list of the cards, separated by space, in one line,in a sorted order, ex: "2S 5D 10H"
    virtual ~Hand();
    bool Check_for_4(Card& card);
    std::vector<Card*>& getVec();
};
#endif
