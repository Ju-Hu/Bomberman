#ifndef CREDITS_H
#define CREDITS_H

#include "config.h"

class Credits : public QGraphicsItemGroup
{
public:


    Credits();

    ~Credits();

private:

    QGraphicsTextItem* text;
};


#endif