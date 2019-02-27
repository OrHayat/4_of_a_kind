#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "Deck.h"
#include "Player.h"

class Game {
private:
        std::vector<Player *> players;  //The list of the players
	Deck deck;                 //The deck of the game
	int turns_counter;
        std::vector<Player *> winners;
public:
	Game(char* configurationFile);
         int Card_Counter;//
         ~Game();
         Game(const Game &other);
         int verbal;
         Game& operator=(const Game &other);
	void init();
	void play();//TODO
	void printState();        //Print the state of the game as described in the assignment.
	void printWinner();       //Print the winner of the game as describe in the assignment.
        void printNumberOfTurns(); //Print the number of played turns at any given time.  
        void removeSpaces(string &str);//gets a string(pass by ref.) and remove all the spaces in the beggining, end and replace all 2-or-more consecutive spaces in the middle with a single space
        Card* translte_card(string &word,int N);
        void printState_pre_turn();
};

#endif
