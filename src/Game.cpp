#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using std::string;
#include <queue>
#include <algorithm>
#include <iterator>
#include "../include/Game.h"
    Game::Game(char* configurationFile):players(std::vector<Player *>()),deck(),turns_counter(0),winners(std::vector<Player *>()),Card_Counter(0),verbal(-1)
    {   
 
    std::ifstream configFile(configurationFile);
    std::queue <string> linesToRead;
    std::string str;
    while (std::getline(configFile,str))//read from file
    {
        removeSpaces(str);//pass by ref., changes str itself. the change is remove all the starting, ending and double spaces.
        if(str!=""&&str.at(0)!='#'){
            linesToRead.push(str);
        }
    }
    
    
    //set  verbal
    string tmp=linesToRead.front();
    linesToRead.pop(); 
    if(tmp=="0")
        this->verbal=0;
    else if(tmp=="1")
        this->verbal=1;
    else{
        std::cout<<"verbal wasnt sent correctly.";
    }
    
    //set int for Card_Counter
    tmp=linesToRead.front();
    linesToRead.pop();
    this->Card_Counter= std::stoi(tmp);
    //set string for deck
    string deckString=linesToRead.front();
    linesToRead.pop();

    while(deckString.length()>0)
    {
        unsigned int cardLength=deckString.length();
        if(deckString.find(' '))
            
            cardLength=deckString.find_first_of(' ');
        string card=deckString.substr(0, cardLength);
        if(deckString.length()>cardLength)
        {
            deckString=deckString.substr(cardLength+1, deckString.length());
            removeSpaces(deckString);
        }
        else
            deckString="";
        this->deck.push(translte_card(card,this->Card_Counter));
        
    }
    
    //NOTE at this point queue linesToRead is to contain the strings for the players(and nothing but)
    
    int t=(int) linesToRead.size();
    while(!linesToRead.empty()){
        t--;
       string pl = linesToRead.front();
       linesToRead.pop();
       int len=pl.find_first_of(' ');
       string name=pl.substr(0, len);
       char num = (pl.at(pl.length()-1));
       switch (num)//insert player into players vector on heap
       {
            case '1' :
            {
                this->players.push_back(new PlayerType1(name, this->Card_Counter));
                break;
            }
            case '2' :
            {   this->players.push_back(new PlayerType2(name, this->Card_Counter));
                break;
            }
            case '3' :
            {
                this->players.push_back(new PlayerType3(name, this->Card_Counter));
                break;
            }
            case '4':
            {
                this->players.push_back(new PlayerType4(name, this->Card_Counter));
                break;
            }
        default:
            std::cout<<"error occured- figure player without type";                
    }
    
   
    
    }
    
    }
    //game constrctor
    
    
void Game::removeSpaces(string &str){//gets a string(pass by ref.) and remove all the spaces in the beggining, end and replace all 2-or-more consecutive spaces in the middle with a single space
    while(str.find("  ")!=std::string::npos){
        str.replace(str.find("  "), 2, " ");
    }
    if(str.length()>0&&str.at(0)==' ')
        str.replace(0, 1, "");
    if(str.length()>0&&str.at(str.length()-1)==' ')
        str.replace(str.length()-1, 1, "");
    
}


Game::~Game()
{
    
    for(unsigned int i=0;i<this->players.size();i++)
    {
        delete (this->players[i]);
    }
}

Game::Game(const Game &other):players(std::vector<Player*>()),deck(),turns_counter(other.turns_counter),winners(),Card_Counter(other.Card_Counter),verbal(other.verbal)//game copy constrctor
{
    
    
    
    std::vector<Card*> d=other.deck.getVec();
    
    for(int i=other.deck.deck_index;i<other.deck.Get_Deck_Size();i++)
    {
            std::string card_name=d[i]->toString();
            Card* tmp2;
            if(card_name[0]=='K'||card_name[0]=='Q'||card_name[0]=='A'||card_name[0]=='J')
            {
                tmp2=new FigureCard(dynamic_cast<FigureCard&>(*d[i]));                
            }
            else
            {
                tmp2=new NumericCard(dynamic_cast<NumericCard&>(*d[i]));
            }
            this->deck.push(tmp2);
    }
    
    
    
    for(unsigned int i = 0; i < other.players.size(); i++){//copy players vector into new player vector.
        Player* p=other.players[i];
        int t=p->type;
        Player* np;
        if(t==1)
        {
            np=new PlayerType1(p->getName(), Card_Counter);
        }
        else if(t==2){
            np=new PlayerType2(p->getName(), Card_Counter);
        }
        else if(t==3){          
            np=new PlayerType3(p->getName(), Card_Counter);
        }
        else if(t==4){       
            np=new PlayerType4(p->getName(), Card_Counter);
        }
        
        np->lastPlayed=p->lastPlayed;
        vector<Card*> vec=p->getVec();
        for(unsigned int i = 0; i<vec.size(); ++i){
            
            std::string card_name=vec[i]->toString();
            Card* tmp;
            if(card_name[0]=='K'||card_name[0]=='Q'||card_name[0]=='A'||card_name[0]=='J')
            {
                tmp=new FigureCard(dynamic_cast<FigureCard&>(*vec[i]));                
            }
            else
            {
                tmp=new NumericCard(dynamic_cast<NumericCard&>(*vec[i]));
            }
            np->addCard(*tmp);
            delete tmp;
            
        }
        
        players.push_back(np);
    }
        for(unsigned int i = 0; i < other.winners.size(); i++){//copy winners list
        Player* p=other.winners[i];
        int t=p->type;
        Player* np;
        if(t==1)
            {
                np=new PlayerType1(p->getName(), Card_Counter);
            
            }
            else if(t==2){
                np=new PlayerType2(p->getName(), Card_Counter);
            }
            else if(t==3){          
                np=new PlayerType3(p->getName(), Card_Counter);
            }
            else if(t==4){       
                np=new PlayerType4(p->getName(), Card_Counter);
            }
            winners.push_back(np);
            }
    
}


        Game& Game::operator=(const Game &other)//game copy assigment operator
        {
            
            
            if(&other==this)
            return *this;
            else
            {
                 for(unsigned int i=0;i<this->players.size();i++)
            {
            delete (this->players[i]);
            }
            delete this;           
            Game* ans=new Game(other);
            this->deck=ans->deck;
            this->players=ans->players;
            this->turns_counter=ans->turns_counter;
            this->winners=ans->winners;
            this->Card_Counter=ans->Card_Counter;
            this->verbal=ans->verbal;
            return *this;
        }
}
            

       Card* Game::translte_card(std::string &word,int N)//get string of card return new card pointer
 {                          
     int len=word.length();
                            char ch = word[len-1];
                            Shape s;
                            switch(ch)
                            {
                                case 'C':
                                {
                                s=Club;
                                break;                                    
                                }
                                case'D':
                                {
                                 s=Diamond;
                                 break;   
                                }
                                case'S':
                                {
                                s=Spade;    
                                break;                                
                                }
                                case'H':
                                {
                                s=Heart;
                                break;
                                }
                                std::cout<<"bug in cards inialazition..";
                            }
                            char is_fig=word[0];
                        if(is_fig=='K'||is_fig=='A'||is_fig=='Q'||is_fig=='J')
                        {
                            Figure t;
                            switch(is_fig)
                            {
                                case'K':
                                {
                                t=King;    
                                break;
                                }
                                
                                case'A':
                                {
                                t=Ace;
                                break;
                                }
                                case 'Q':
                                {
                                t=Queen;
                                break;                                    
                                }
                                case 'J':
                                {
                                t=Jack;
                                break;    
                                }
                            }//switch      
                            return new FigureCard(t,s,N);
}                             else//number card
                        {
                            int Num=-1;
                            std::string number_s=word.std::string::substr(0,len-1);
                            Num=std::stoi(number_s);
                            return new NumericCard(Num,s); 
                        }
 }
 
 
 void Game::printWinner()//print winners
 {
     if(this->winners.size()==1)
         std::cout<<"***** The Winner is: "<<this->winners[0]->getName()<<" *****\n";
     else
     {         std::cout<<"***** The winners are: "<<this->winners[0]->getName();
         for(unsigned int i=1;i<this->winners.size();i++)
         {std::cout<<" and "<<this->winners[i]->getName();
        }
        std::cout<<" *****\n";         
    }
     
}
 void Game::printNumberOfTurns()//print number of turns
    {
     std::cout<<"Number of turns: "<<this->turns_counter <<"\n";
    }
 
 void Game::init()//init the game
 {
     for(unsigned int i=0;i<players.size();i++)
     {
         for(int j=0;j<7;j++)
         {//draw 7 cards 
             
             Card* card=this->deck.fetchCard();
             players[i]->addCard(*card);
             if(players[i]->Check_for_4(*card)==true)
             {
                                 std::string card_name=card->toString();
 
                //NOTE CONVERT card            
                if(card_name[0]=='K'||card_name[0]=='Q'||card_name[0]=='A'||card_name[0]=='J')
                {
                    FigureCard* tmp;//card pointer checking for 4 on initalztion.
                    tmp=new FigureCard(dynamic_cast<FigureCard&>(*card));
                    Figure F=tmp->GetFigure();
                    delete tmp;
                    FigureCard c1(F,Club,this->Card_Counter);
                    FigureCard c2(F,Diamond,this->Card_Counter);
                    FigureCard c3(F,Heart,this->Card_Counter);
                    FigureCard c4(F,Spade,this->Card_Counter);
                    this->players[i]->removeCard(c1);
                    this->players[i]->removeCard(c2);
                    this->players[i]->removeCard(c3);
                    this->players[i]->removeCard(c4);
                }
                else
                {
                    NumericCard* tmp2;
                    tmp2=new NumericCard(dynamic_cast<NumericCard&>(*card));
                    int num=tmp2->GetNumber();
                    delete tmp2;
                    NumericCard t1(num,Club);
                    NumericCard t2(num,Diamond);
                    NumericCard t3(num,Heart);
                    NumericCard t4(num,Spade);
                    this->players[i]->removeCard(t1);
                    this->players[i]->removeCard(t2);
                    this->players[i]->removeCard(t3);
                    this->players[i]->removeCard(t4);
                }
            }             
        }
    }
      this->turns_counter=1;
}

void Game::printState_pre_turn()//print game state each turn
{
    std::cout<<"\nTurn "<<this->turns_counter<<"\n";
    this->printState();
}


void Game::printState()//print state of game as requied
{
    std::cout<<"Deck: "<<this->deck.toString()<<"\n";
    for(unsigned int i=0;i<this->players.size();i++)
    {
      std::cout<<players[i]->getName()<<": "<<players[i]->toString()<<"\n";  
    }
}

void Game::play()//play the game
{
    int ct=0;
    bool winner=false;
    while(!winner)
    {
        string cardAsked=players[ct]->cardToAsk();
        string test = players[ct]->toString();
        int playerAsked=players[ct]->playerToAsk(players);
        string askerName=players[ct]->getName();
        string askedName=players[playerAsked]->getName();        
                if(this->verbal==1)
        {
            this->printState_pre_turn();
            std::cout<<askerName<<" asked "<<askedName<< " for the value "<<cardAsked<<"\n";
        }
        int counter=0;
        if(cardAsked[0]=='K'||cardAsked[0]=='A'||cardAsked[0]=='Q'||cardAsked[0]=='J')
        {
            Figure f;
            if(cardAsked[0]=='K')
            {
                f=King;
            }
            if(cardAsked[0]=='Q')
            {
                f=Queen;
            }
            if(cardAsked[0]=='J')
            {f=Jack;
                
            }
            if(cardAsked[0]=='A')
            {
            f=Ace;
            }
            
                        FigureCard fig1(f,Club,this->Card_Counter);
                        FigureCard fig2(f,Diamond,this->Card_Counter);
                        FigureCard fig3(f,Heart,this->Card_Counter);
                        FigureCard fig4(f,Spade,this->Card_Counter);
                        if(players[playerAsked]->search(fig1)){
                            counter++;
                            players[playerAsked]->removeCard(fig1);
                            players[ct]->addCard(fig1);
                        }
                        if(players[playerAsked]->search(fig2)){
                            counter++;
                            players[playerAsked]->removeCard(fig2);
                            players[ct]->addCard(fig2);
                        }
                        if(players[playerAsked]->search(fig3)){
                            counter++;
                            players[playerAsked]->removeCard(fig3);
                            players[ct]->addCard(fig3);
                        }
                        if(players[playerAsked]->search(fig3)){
                            counter++;
                            players[playerAsked]->removeCard(fig3);
                            players[ct]->addCard(fig3);
                        }
                        if(players[playerAsked]->search(fig4)){
                            counter++;
                            players[playerAsked]->removeCard(fig4);
                            players[ct]->addCard(fig4);
                        }
                        if(players[ct]->Check_for_4(fig1)==true)
                        {
                            players[ct]->removeCard(fig1);
                            players[ct]->removeCard(fig2);
                            players[ct]->removeCard(fig3);
                            players[ct]->removeCard(fig4);
                        }
        }
        else//its NumericCard
        {
            int nb=std::stoi(cardAsked);
            NumericCard num1(nb,Club);
            NumericCard num2(nb,Diamond);
            NumericCard num3(nb,Heart);
            NumericCard num4(nb,Spade);
        //search those cards
        if(players[playerAsked]->search(num1)){
            counter++;
            players[playerAsked]->removeCard(num1);
            players[ct]->addCard(num1);
        }
        if(players[playerAsked]->search(num2)){
                counter++;
                players[playerAsked]->removeCard(num2);
                players[ct]->addCard(num2);
            }        
            if(players[playerAsked]->search(num3)){
                counter++;
                players[playerAsked]->removeCard(num3);
                players[ct]->addCard(num3);
            }
            if(players[playerAsked]->search(num4)){
                counter++;
                players[playerAsked]->removeCard(num4);
                players[ct]->addCard(num4);
            }
            
                                    if(players[ct]->Check_for_4(num1)==true)
                        {
                            players[ct]->removeCard(num1);
                            players[ct]->removeCard(num2);
                            players[ct]->removeCard(num3);
                            players[ct]->removeCard(num4);
                        }

            
            
        }
        if(counter==0){
            if(this->deck.getNumberOfCards()>0 && players[ct]->GetNumberOfCards()>0)//player failled to guess card
            {
                
                Card* tmp =this->deck.fetchCard();
                this->players[ct]->addCard(*tmp);
                if(players[ct]->Check_for_4(*tmp))
                    players[ct]->remove_4(*tmp);

            }
        }
        else
        {
            if(this->players[playerAsked]->GetNumberOfCards()>0)//other player has cards in hand after player took cards from him?
            {
            while(counter>0){
                
                if(this->deck.getNumberOfCards()>0)//draw from deck
                {
                    Card* tmp =this->deck.fetchCard();
                    this->players[playerAsked]->addCard(*tmp);
                    bool flag=(players[playerAsked]->Check_for_4(*tmp));
                        if (flag)
                        {
                            players[playerAsked]->remove_4(*tmp);
                        }
                }
                counter--;
                }
            }
           else{counter=0;} 
        }

        for(unsigned int i=0;i<this->players.size();i++)//check for winners
        {
            if(this->players[i]->GetNumberOfCards()==0)
            {
                this->winners.push_back(this->players[i]);
                winner=true;
            }
        }
        ct=(ct+1)%this->players.size();//update turns
        if(!winner)
        {this->turns_counter++;}
    }
    
}



 
 