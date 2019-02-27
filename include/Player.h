#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <vector>
#include <Hand.h>

using namespace std;

class Player : public Hand {
private:
	const string name;
        
protected:

public:
        virtual int playNext(vector<Player*> &players);
        int type;//keeps the type of the player
        int lastPlayed;//last player this player asked from
        virtual string cardMostOf();//used to find the value of the card that this player has most of
        virtual string  cardLeastOf();//used to find the value of the card that this player has least of
        int findPWMostCards(vector<Player*> &players);
        string maxVal();//returns the highest value this player holds
        string minValue();//returns the lowest value this player holds

        Player(string name, int cn, int t);
        Player(const Player &other);
        virtual ~Player();
        string getName();   //Returns the name of the player
        virtual int playerToAsk(vector<Player*> &players)=0;//returns the next player this player will ask from
        virtual string cardToAsk()=0;//returns the next card this player will ask for

};


//playeTypeX has 2 main methods:
//playerToAsk gets the vector of players(it doesn't chnge it) and returns int that represent the place in the vector that the player should ask from
//cardToAsk returns the value of the card this player will ask for.
class PlayerType1 : public Player 
{  //For strategy 1
    public: 
        PlayerType1(string name, int cn);
    PlayerType1& operator=(const PlayerType1 &other);
    PlayerType1(const PlayerType1 &other);
        int playerToAsk(vector<Player*> &players);//returns the next player this player will ask from
        string cardToAsk();//returns the next card this player will ask for
PlayerType1(const Player &other);
//...
;
};

class PlayerType2 : public Player {  //For strategy 2
//...

    public: PlayerType2(string name, int cn);
    PlayerType2& operator=(const PlayerType2 &other);
    PlayerType2(const PlayerType2 &other);
        int playerToAsk(vector<Player*> &players);//returns the next player this player will ask from
        string cardToAsk();//returns the next card this player will ask for

            PlayerType2(const Player &other);

};

class PlayerType3 : public Player {  //For strategy 3
//...

    public:
        PlayerType3(string name, int cn);
        PlayerType3& operator=(const PlayerType3 &other);
        PlayerType3(const PlayerType3 &other);
        int playerToAsk(vector<Player*> &players);//returns the next player this player will ask from
        string cardToAsk();//returns the next card this player will ask for
        PlayerType3(const Player &other);

};

class PlayerType4 : public Player {  //For strategy 4
//...

    public:
        PlayerType4(string name, int cn);
        PlayerType4& operator=(const PlayerType4 &other);
        PlayerType4(const PlayerType4 &other);
        int playerToAsk(vector<Player*> &players);//returns the next player this player will ask from
        string cardToAsk();//returns the next card this player will ask for
        PlayerType4(const Player &other);

};


#endif
