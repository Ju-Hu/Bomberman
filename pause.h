#ifndef PAUSE_H
#define PAUSE_H


#include "menubutton.h"
#include "config.h"

class Pause : public QGraphicsItemGroup
{
public:


    Pause();
 
    ~Pause();

    MenuButton* getContinueBtn() const;

    MenuButton* getBackMenuBtn() const;

private:

    MenuButton* continueBtn;

    MenuButton* backMenuBtn;

    QGraphicsTextItem* title;
};

#endif