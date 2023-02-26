#include "victory.h"

Victory::Victory()
{
    backMenuBtn2 = new MenuButton("Menu");

    int yOffset = 120;
    int borderOffset = 50;

    // rectangle
    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, backMenuBtn2->width() + borderOffset, 400); //yOffset * 3 + borderOffset
    rect->setBrush(Qt::white);
    rect->setPos((MAP_WIDTH / 2) - (backMenuBtn2->width() / 2) - (borderOffset / 2), MAP_HEIGHT / 2 - 200); //+ yOffset - borderOffset / 2
    this->addToGroup(rect);

    // menu title
    title = new QGraphicsTextItem("Player 1\nWon!");
    QFont font = QFont("Agency FB", 60);
    font.setBold(true);
    title->setFont(font);
    title->setPos(MAP_WIDTH / 2 - 170 / 2, MAP_HEIGHT / 2 - 200);
    addToGroup(title);

    // Set button in the midle of the screen
    backMenuBtn2->move(MAP_WIDTH / 2 - backMenuBtn2->width() / 2, MAP_HEIGHT / 2 - 200 + yOffset * 2);
}

Victory::~Victory()
{
    delete backMenuBtn2;
    delete title;
}

MenuButton* Victory::getBackMenuBtn2() const
{
    return backMenuBtn2;
}