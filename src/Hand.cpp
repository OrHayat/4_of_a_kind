#include <algorithm>
#include <vector>
#include "../include/Hand.h"
//#include <iterator>//maybe


Hand::Hand(int N):hand_cards(new std::vector<Card*>()),num_cards(N)
{
//    this->num_cards=N;
}

Hand::Hand(const Hand &other):hand_cards(new std::vector<Card*>(*other.hand_cards)),num_cards(other.num_cards)
{
    
    std::cout<<"hand was copied\n";
}
void Hand::remove_4(Card &card)//remove 4 cards from same kind of given refrence assume cards exsist on hand.
{
               std::string card_name=card.toString();             
                if(card_name[0]=='K'||card_name[0]=='Q'||card_name[0]=='A'||card_name[0]=='J')
                {
                    FigureCard* tmp;
                    tmp=new FigureCard(dynamic_cast<FigureCard&>(card));
                    Figure F=tmp->GetFigure();
                    delete tmp;
                    FigureCard c1(F,Club,this->num_cards);
                    FigureCard c2(F,Diamond,this->num_cards);
                    FigureCard c3(F,Heart,this->num_cards);
                    FigureCard c4(F,Spade,this->num_cards);
                    this->removeCard(c1);
                    this->removeCard(c2);
                    this->removeCard(c3);
                    this->removeCard(c4);
                }
                else
                {
                    NumericCard* tmp2;
                    tmp2=new NumericCard(dynamic_cast<NumericCard&>(card));
                    int num=tmp2->GetNumber();
                    delete tmp2;
                    NumericCard t1(num,Club);
                    NumericCard t2(num,Diamond);
                    NumericCard t3(num,Heart);
                    NumericCard t4(num,Spade);
                    this->removeCard(t1);
                    this->removeCard(t2);
                    this->removeCard(t3);
                    this->removeCard(t4);
                }
               
}
        bool Hand::search(Card &card)//search the card on hand return true if found false otherwise.
        {//NOTE using card_number need to know N from game/.
            for(unsigned int i=0;i<this->hand_cards->size();i++)
            {
                if(card.card_points==this->hand_cards->at(i)->card_points)
                   return true;
            }
            return false;
        }

                bool Hand::Check_for_4(Card &card)//check if 4 cards of same kind of given card refrence exsist on hand
                {
                    if(this->GetNumberOfCards()<4)
                    {
                           return false;
                    }
                    else
                    {
                std::string card_name=card.toString();
                int counter=0;
                //NOTE CONVERT card            
                if(card_name[0]=='K'||card_name[0]=='Q'||card_name[0]=='A'||card_name[0]=='J')
                {
                                    FigureCard* tmp;
                    tmp=new FigureCard(dynamic_cast<FigureCard&>(card));
                    Figure F=tmp->GetFigure();
                    delete tmp;
                    FigureCard c1(F,Club,this->num_cards);
                    FigureCard c2(F,Diamond,this->num_cards);
                    FigureCard c3(F,Heart,this->num_cards);
                    FigureCard c4(F,Spade,this->num_cards);
                    //search those cards count how many were found.
                    if(this->search(c1))
                    {
                        counter++;
                    }
                    if(this->search(c2))
                    {
                        counter++;
                    }
                    if(this->search(c3))
                    {
                        counter++;
                    }
                    if(this->search(c4))
                    {
                        counter++;
                    }
                    if(counter==4)// do hand has 4 cards of same kind?
                        return true;
                    else 
                        return false;
                }
                else
                {
                    NumericCard* tmp2;
                    
                    tmp2=new NumericCard(dynamic_cast<NumericCard&>(card));
                    int nb=tmp2->GetNumber();
                    delete tmp2;
                    NumericCard t1(nb,Club);
                    NumericCard t2(nb,Diamond);
                    NumericCard t3(nb,Heart);
                    NumericCard t4(nb,Spade);
                    
                    if(this->search(t1))
                    {
                        counter++;
                    }
                    if(this->search(t2))
                    {
                        counter++;
                    }
                    if(this->search(t3))
                    {
                        counter++;
                    }
                    if(this->search(t4))
                    {
                        counter++;
                    }
                    if(counter==4)
                        return true;
                    else return false;
                }                    
    }
                }
          int Hand::GetNumberOfCards()
          {// return HAND size
         return (this->hand_cards->size());
          }
          
	bool Hand::addCard(Card &card)//add card to hand with given card refrence.
        {//TODO add card with refrence  need casting //NOTE
            if(this->search(card)==true)
            {
                std::cout<<"trying to insert card that already exist-the card is "<<card.toString()<<'\n';
                return false;
            }
            else
            {
                //NOTE add new card
                std::string card_name=card.toString();
                Card* tmp;
                if(card_name[0]=='K'||card_name[0]=='Q'||card_name[0]=='A'||card_name[0]=='J')
                {
                    tmp=new FigureCard(dynamic_cast<FigureCard&>(card));                
                }
                else
                {
                    tmp=new NumericCard(dynamic_cast<NumericCard&>(card));
                }
            this->hand_cards->push_back(tmp);
           // std::cout<<"card was inserted \n"<<this->toString();
            return true;
            }
        }
        bool Hand::removeCard(Card &card)//remove card from hand assume card exsist on HAND
        //TODO removeCard with refrence.
        {
            for(int i=0;i<this->GetNumberOfCards();i++)
            {
                if(card.card_points==this->hand_cards->at(i)->card_points)
                {
                    delete(this->hand_cards->at(i));
            this->hand_cards->erase (this->hand_cards->begin()+i);
                    return true;
                }
            }
                return false;
        }
        

        
            bool Compare_Cards(Card* a,Card* b) //comparision of cards for sorting the hand.
            { return (*a < *b); 
                
            }  
            //TODO FIX THIS SORT
        std::string Hand::toString()//sort the hand and return it sorted.
        {
           std::sort(hand_cards->begin(),hand_cards->end(),Compare_Cards);
           std::string res="";
           for(int i=0;i<this->GetNumberOfCards();i++)
           {
            res=res+this->hand_cards->at(i)->toString();
            if(i<this->GetNumberOfCards()-1)
                res=res+" ";
        }
        return res;
           }
           

        Hand& Hand::operator=(const Hand &other)//hand assigment operator
        {
        if(this==&other)
            {
                        return *this;
            }
        else
            {
            for(int i=0;i<this->GetNumberOfCards();i++)
                {
                delete(this->hand_cards->at(i));
                }
            delete this->hand_cards;
                std::vector<Card*>* tmp =new std::vector<Card*>(*other.hand_cards);
                this->num_cards=other.num_cards;
                this->hand_cards=tmp;
                return *this;
    }
    
    
    
}
        Hand::~Hand()//hand destrctor
        {
            for(int i=0;i<this->GetNumberOfCards();i++)
            {
                delete(this->hand_cards->at(i));
            }
            delete this->hand_cards;
        }
        std::vector<Card*>& Hand::getVec()
        {
            std::sort(hand_cards->begin(),hand_cards->end(),Compare_Cards);
            return *hand_cards;
        }
       