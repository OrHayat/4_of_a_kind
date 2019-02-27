#include "../include/Player.h"
#include <vector>
#include <string>
std::string Player::getName()//Returns the name of the player
{
    return this->name;
}
        
Player::Player(string name, int cn, int t):Hand(cn),name(name),type(t),lastPlayed(0)
{
}
        
        
PlayerType1::PlayerType1(string name, int cn):Player(name, cn, 1)
{   
}
string PlayerType1::cardToAsk(){
    return cardMostOf();
}
    
int PlayerType1::playerToAsk(vector<Player*> &players){
    return Player::findPWMostCards(players);
}
    
    
PlayerType2::PlayerType2(string name, int cn):Player(name, cn, 2)
{
}
    string PlayerType2::cardToAsk(){
        return cardLeastOf();
    }
    
    
    int PlayerType2::playerToAsk(vector<Player*> &players){
        return Player::findPWMostCards(players);
    }
    
PlayerType3::PlayerType3(string name, int cn):Player(name, cn, 3)
{

}
string PlayerType3::cardToAsk(){
    return maxVal();
}
    
int PlayerType3::playerToAsk(vector<Player*> &players){
    return playNext(players);
}


PlayerType4::PlayerType4(string name, int cn):Player(name, cn, 4)
{


}
string PlayerType4::cardToAsk(){
    return minValue();
}
int PlayerType4::playerToAsk(vector<Player*> &players){
    return playNext(players);
}

int Player::playNext(vector<Player*> &players)
{
    int numOfPlayers= players.size();
    int ans=(this->lastPlayed)%numOfPlayers;
    string n=players[ans]->getName();
    if(this->name==n){
        ans=(ans+1)%numOfPlayers;
        this->lastPlayed=(this->lastPlayed+1)%numOfPlayers;    
        
    }
    this->lastPlayed=(this->lastPlayed+1)%numOfPlayers;
    return ans;    
}
Player::~Player()
{
}

string Player::minValue(){
    vector<Card*> vec=this->getVec();
    string ans = vec[0]->toString();
    ans=ans.substr(0, ans.length()-1);
    return ans;
}
    string Player::maxVal(){
        vector<Card*> hnd=this->getVec();
        string ans = hnd[hnd.size()-1]->toString();
        ans=ans.substr(0, ans.length()-1);
        return ans;
    }

    string Player::cardMostOf(){
    string last="";
    int lastAmount=0;
    string max="";
    int maxAmount=0;
    vector<Card*> hnd=this->getVec();
    for(unsigned i = 0; i < hnd.size(); ++i){

        string tmp=hnd[i]->toString();
        tmp=tmp.substr(0, tmp.length()-1);
        if(tmp!=last){
            last=tmp;
            lastAmount=1;
            if(lastAmount>=maxAmount){
                max=last;
                maxAmount=lastAmount;
            }
        }
        else{
            ++lastAmount;
            if(lastAmount>=maxAmount){
                max=last;
                maxAmount=lastAmount;
            }
        }
    }
    return max;
}


string Player::cardLeastOf(){
    std::vector<Card*> hnd=this->getVec();

    int lastAmount=1;
    string min=hnd[0]->toString();
    min=min.substr(0, min.length()-1);
    int minAmount=1;
    string last=min;
    for(unsigned i = 1; i < hnd.size(); ++i){
        string tmp=hnd[i]->toString();
        tmp=tmp.substr(0, tmp.length()-1);
        
        if(tmp!=last){
            if(lastAmount<minAmount){
                min=last;
                minAmount=lastAmount;
            }
            last=tmp;
            lastAmount=1;
        }
        else{
            ++lastAmount;
            if(last==min)
                minAmount++;
        }

    }
    if(lastAmount<minAmount){
        min=last;
        minAmount=lastAmount;
    }
    return min;
}



PlayerType1& PlayerType1::operator=(const PlayerType1 &other)
{
    return *this;
}
PlayerType2& PlayerType2::operator=(const PlayerType2 &other)
{
    return *this;
}
PlayerType3& PlayerType3::operator=(const PlayerType3 &other)
{
    return *this;
}
PlayerType4& PlayerType4::operator=(const PlayerType4 &other)
{
    return *this;
}

//copy constructor
Player::Player(const Player &other):Hand(other),name(other.name),type(other.type),lastPlayed(other.lastPlayed)
{
    
}
//playerTypeX have no fields, so coppy constructors just calls the ctor of player
PlayerType1::PlayerType1(const PlayerType1 &other):Player(other){}
PlayerType2::PlayerType2(const PlayerType2 &other):Player(other){}
PlayerType3::PlayerType3(const PlayerType3 &other):Player(other){}
PlayerType4::PlayerType4(const PlayerType4 &other):Player(other){}

PlayerType1::PlayerType1(const Player &other):Player(other){}
PlayerType2::PlayerType2(const Player &other):Player(other){}
PlayerType3::PlayerType3(const Player &other):Player(other){}
PlayerType4::PlayerType4(const Player &other):Player(other){}


int Player::findPWMostCards(vector<Player*> &players)
{
    int ans=0;
    int max=0;
    for(unsigned i=0; i<players.size(); ++i){
        string n=players[i]->getName();
        if(this->name!=n){
            int othersCards=players[i]->GetNumberOfCards();
            if(othersCards>=max){
                max=othersCards;
                ans=(int) i;
            }
        }
    }
    return ans;
}









