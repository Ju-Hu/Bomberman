#include "pause.h"

Pause::Pause()
{
    continueBtn = new MenuButton("Continue");
    continueBtn->setStyleSheet("border-image:url(images/continuebutton.png);");
    backMenuBtn = new MenuButton("Menu");
    backMenuBtn->setStyleSheet("border-image:url(images/quitbutton.png);");

    int yOffset = 120;
    int borderOffset = 50;

    // rectangle
    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, continueBtn->width() + borderOffset, 400); //yOffset * 3 + borderOffset
    rect->setBrush(Qt::lightGray);
    rect->setPos((MAP_WIDTH / 2) - (continueBtn->width() / 2) - (borderOffset / 2), MAP_HEIGHT/2 - 200); //+ yOffset - borderOffset / 2
    this->addToGroup(rect);

    // menu title
    title = new QGraphicsTextItem("Pause");
    QFont font = QFont("Agency FB", 60);
    font.setBold(true);
    title->setFont(font);
    title->setPos(MAP_WIDTH / 2 - 170 / 2, MAP_HEIGHT / 2 - 200);
    addToGroup(title);

    // Set button in the midle of the screen
    continueBtn->move(MAP_WIDTH / 2 - continueBtn->width() / 2, MAP_HEIGHT / 2 - 200 + yOffset);
    backMenuBtn->move(MAP_WIDTH / 2 - backMenuBtn->width() / 2, MAP_HEIGHT / 2 - 200 + yOffset * 2);


}

Pause::~Pause()
{
    delete continueBtn;
    delete backMenuBtn;
    delete title;
}

MenuButton* Pause::getContinueBtn() const
{
    return continueBtn;
}

MenuButton* Pause::getBackMenuBtn() const
{
    return backMenuBtn;
}