#include "../include/Deck.h"
#include  "../include/Hand.h"

Deck::Deck():deck(new std::vector<Card*>()),deck_size(0),deck_index(0)
{
    //this->deck_size=size;
    //this->deck=deck;
}

void Deck::push(Card* card)
{
    this->deck->push_back(card);
    this->deck_size++;
    
}

Deck::Deck(std::vector<Card*>* deck,int size):deck(deck),deck_size(size),deck_index(0)
{
    //this->deck_size=size;
    //this->deck=deck;
}
Deck::Deck(const Deck &other):deck(new std::vector<Card*>(*other.deck)),deck_size(other.deck_size),deck_index(other.deck_index)
{
}

Deck & Deck::operator=(const Deck &other)//copy assigment operator
{
    if(this==&other)
    {
        return *this;
    }
        for(unsigned int i=0;i<this->deck->size();i++)
            {
                delete this->deck->at(i);                
            }
            delete this->deck;
            this->deck_size=other.deck_size;
     std::vector<Card*>* tmp =new std::vector<Card*>(*other.deck);
    this->deck=tmp;
    return *this;
}
void Deck::insert_NumCard(int n,Shape s)
{
    NumericCard* ca=new NumericCard(n,s);
    this->deck->push_back(ca);
}

    void Deck::insert_FigCard(Figure f,Shape s,int max_Numeric)
{
     FigureCard* c=new FigureCard(f,s,max_Numeric);
     this->deck->push_back(c);
}

            int Deck::getNumberOfCards()
            {
             return this->deck_size-this->deck_index;//might need stl list  instead  
            }
            
            std::string Deck::toString()
        {
           std::string s="";
            for(int i=this->deck_index;i<this->deck_size;i++)
            {

                s=s+this->deck->at(i)->toString();
                if(i<this->deck_size-1)
                    s=s+" ";
            }
            return s;
        }
        
        Card* Deck::fetchCard()//assume deck still have cards left to deal
        {
            Card* res=this->deck->at(this->deck_index);
            this->deck_index++;
            return res;
        }

          Deck::~Deck()//destrctor
          {
              for(unsigned int i=0;i<this->deck->size();i++)
            {
                delete this->deck->at(i);                
            }
            delete this->deck;
            }
                    std::vector<Card*>& Deck::getVec()const
        {
            return *(this->deck);
        }
int Deck:: Get_Deck_Size()const//return the deck size
{
    return this->deck_size;
}
    


    
    
    
    