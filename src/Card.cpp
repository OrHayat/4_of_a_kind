#include "../include/Card.h"



using namespace std;
        void test()
        {
         //   NumericCard x=new NumericCard(2,Diamond);
            NumericCard x(2,Diamond);
            std::string test=x.toString();
         //   std::cout<<"test"<<std::endl;
         bool flag=(test=="2D");
           // std::cout<<"  2d =2d? "<<std::boolalpha<<flag<<std::endl;
            FigureCard tmp(King,Heart,54);
            string y=tmp.toString();
            cout<<y<<"kh?"<<endl;
            cout<<endl;
            std::cout<<"  KH =KH? "<<std::boolalpha<<flag<<std::endl;
            
            cout<<endl;
            cout<<"is 2d<KH?"<<(x<tmp)<<endl;
         //   delete x;
        }


std::string Card::set_type(Shape shape)
{
    string s="";
     if(shape==Club)
    {
        s="C";
    }
    else if(shape==Diamond)
    {
        s="D";
    }
    else if(shape==Heart)
    {
        s="H";
    }
    else if(shape==Spade)
    {
    return s="S";
    }
    else
        std::cout<<"error occured- card without type"; 
    return s;
}

Card::Card(Shape shape):shape(shape),type(set_type(shape))
{  

}
void Card::Set_Shape(Shape shape)
{
    this->shape=shape;
}

    bool Card::operator <(const Card &card2) const 
    { 
        if (this->card_points<card2.card_points)
        return true;
        else return false;
    }
    
    
        bool Card::operator >(const Card &card2) const 
    { 
        if (this->card_points>card2.card_points)
        return true;
        else return false;
    }  
    
    
Card::~Card()
{
    
}
  Shape  Card::GetShape()const
{
    return this->shape;
}
/*
 * 
 *figure card bellow
 * 
 */
    std::string FigureCard::set_figure(Figure figure)
    {
    std::string res="";
    switch(figure)
    {
        case Ace:
        {
            res='A';
            break;
        }
        case King:
        {
            res='K';
            break;
        }
        case Queen:
        {
          res='Q';
          break;
        }
        case Jack:
        {
          res='J';
            break;
        }
        default:
            std::cout<<"error occured- figure card without shape";
    }
    return res;
    }
    


FigureCard::FigureCard(Figure figure,Shape shape,int Player_N):Card(shape),figure(figure),fig_type(set_figure(figure))
{
    int tmp2=0;
    this->figure=figure;
    switch(figure)
    {
        case Ace:
        {
            this->fig_type='A';
            tmp2=Player_N+5;
            break;
        }
        case King:
        {
            this->fig_type='K';
            tmp2=Player_N+4;
            break;
        }
            
        case Queen:
        {
          this->fig_type='Q';
            tmp2=Player_N+3;
          break;
        }
        case Jack:
        {
            tmp2=Player_N+2;
            this->fig_type='J';
            break;
        }
        default:
            std::cout<<"error occured- figure card without shape";
    }
            
            int tmp=0;
            switch(shape)
    {
        case Spade:
        {
            tmp=3;
            break;
        }
        case Heart:
        {
            tmp=2;
            break;
        }
            
        case Diamond:
        {
            tmp=1;
            break;
        }
        case Club:
        {
            tmp=0;
            break;
        }
        default:
            std::cout<<"error occured- figure card without shape";
        }    
            this->card_points=tmp+tmp2*4;
                        
}
        
    FigureCard::FigureCard(const FigureCard& card):Card(card.GetShape()),figure(card.GetFigure()),fig_type(card.Get_Fig_Type())
    {
        this->card_points=card.card_points;
    }    
        
      std::string FigureCard::Get_Fig_Type()const//getter
       {
           return this->fig_type;//NOTE the string one
    }

    
FigureCard& FigureCard::operator=(const FigureCard &other)
{
    if(this==&other)
    {
        return *this;
    }
    else
    {
        this->Set_Shape(other.GetShape());
        this->type=this->set_type(other.GetShape());
        this->card_points=other.card_points;
        this->figure=other.GetFigure();
        this->fig_type=other.Get_Fig_Type();
       return *this;
    }
    
}
FigureCard::~FigureCard()
{
    
}

std::string FigureCard::toString()
{
    std::string s;
    s+=this->fig_type+this->type;
    return s;    
}

Figure FigureCard::GetFigure()const
{
 return this->figure;   
}

/*
 * 
 * numeric card
 * */

NumericCard::NumericCard(int number,Shape shape):Card(shape),number(number),number_string(std::to_string(number))
{
    int tmp=0;
    switch(shape)
    {
        case Spade:
        {
            tmp=3;
            break;
        }
        case Heart:
        {
            tmp=2;
            break;
        }
            
        case Diamond:
        {
          tmp=1;
            break;
        }
        case Club:
        {
            tmp=0;
            break;
        }
        default:
            std::cout<<"error occured- figure card without shape";
            }     
    this->number=number;
    this->card_points=number*4+tmp;
    this->number_string=std::to_string(number);
}

    NumericCard::NumericCard(const NumericCard& card):Card(card.GetShape()),number(card.GetNumber()),number_string(std::to_string(card.GetNumber()))
    {
    //  int nb=card.GetNumber();
       // this->number=nb;
       // this->number_string=std::to_string(nb);
       this->card_points=card.card_points;
    }

    
    
    NumericCard& NumericCard::operator=(const NumericCard &other)
{
    if(this==&other)
    {
        return *this;
    }
    else
    {
        this->Set_Shape(other.GetShape());
        this->type=this->set_type(other.GetShape());
        this->card_points=other.card_points;
        this->number=other.GetNumber();
        this->number_string=std::to_string(other.GetNumber());
       return *this;
    }
}

std::string NumericCard::toString()
{
    std::string s(this->number_string);
    s+=this->type;
    return s; 
}
int NumericCard::GetNumber()const
{
    return this->number;
}

NumericCard::~NumericCard()
{
    
}
