#ifndef VICTORY_H
#define VICTORY_H


#include "menubutton.h"
#include "config.h"

class Victory : public QGraphicsItemGroup
{
public:


    Victory();

    ~Victory();

    MenuButton* getBackMenuBtn2() const;

    //int playerWon = 0;

    QGraphicsTextItem* title;

private:

    MenuButton* backMenuBtn2;

    
};

#endif