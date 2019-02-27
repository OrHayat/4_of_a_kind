#ifndef CARD_H_
#define CARD_H_
#include <string>
#include <iostream>

enum Shape {
	Club,
	Diamond,
	Heart,
	Spade
};

enum Figure {
	Jack,
	Queen,
	King,
	Ace
};

class Card 
{
    
private:
Shape shape;
protected:
std::string set_type(Shape shape);//return string of the type shape
Card(Shape shape);
void Set_Shape(Shape shape);
std::string type;//string name of shape.
public:
    int card_points=0;//card worth in comparison
    Shape GetShape()const;//getter
    bool operator <(const Card &card2) const; // declare only
    bool operator >(const Card &card2) const; // declare only
virtual std::string toString() = 0; //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"
virtual ~Card();    
};

class FigureCard : public Card {
private:
    std::string set_figure(Figure fig);
    Figure figure;
    std::string fig_type;
protected:
public:
    FigureCard(const FigureCard& card);
    FigureCard& operator=(const FigureCard &other);
    Figure GetFigure()const;//getter
    std::string Get_Fig_Type()const;//getter
    FigureCard(Figure figure,Shape shape,int Player_N);
    virtual std::string toString() override;
virtual ~FigureCard();
};

class NumericCard : public Card {
private:
    int number;
protected:
    std::string number_string;
public:
    
    int GetNumber()const;//getter
    NumericCard(int number,Shape shape);
    NumericCard& operator=(const NumericCard &other);
    NumericCard(const NumericCard& card);
    virtual~NumericCard();
    virtual std::string toString() override;
};


#endif