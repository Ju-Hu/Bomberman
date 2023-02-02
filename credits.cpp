#include "credits.h"

Credits::Credits()
{
    int yOffset = 120;
    int borderOffset = 50;
    int width = 500;
    int height = 500;

    // rectangl
    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, width, height);
    rect->setBrush(Qt::white);
    rect->setPos(200, 300);
    this->addToGroup(rect);

    // credits text
    text = new QGraphicsTextItem("Credits\n\nChristopher Busch\nJulian Huenting\n\nWestfaelische Hochschule\nBocholt");
    QFont font = QFont("Agency FB", 40);
    font.setBold(true);
    text->setFont(font);
    text->setPos(200, 300);
    addToGroup(text);

    
}

Credits::~Credits()
{
    delete text;
}