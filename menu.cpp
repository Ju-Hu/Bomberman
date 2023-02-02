#include "menu.h"

//#include <QStyleHints>
Menu::Menu() : QGraphicsScene()
{
    int xButton = 200;
    int yStartButton = 300;
    // Create window scene with background
    //this->setSceneRect(0, 0, MAP_WIDTH, MAP_HEIGHT);
    QImage background = QImage("images/backgrounds/background_menu.png");
    //background = background.scaled(WINDOW_HEIGHT, WINDOW_WIDTH);
    this->setBackgroundBrush(background);

    //// Display levels buttons
    int index = 0;
    
    // LVL1 Btn
    Lvl1Btn = new MenuButton("Level 1");
    Lvl1Btn->move(xButton, yStartButton + index * (Lvl1Btn->height() + BTN_GAP));
    this->addWidget(Lvl1Btn);
    index++;

    // LVL2 Btn
    Lvl2Btn = new MenuButton("Level 2");
    Lvl2Btn->move(xButton, yStartButton + index * (Lvl2Btn->height() + BTN_GAP));
    this->addWidget(Lvl2Btn);
    index++;

    // LVL3 Btn
    Lvl3Btn = new MenuButton("Level 3");
    Lvl3Btn->move(xButton, yStartButton + index * (Lvl3Btn->height() + BTN_GAP));
    this->addWidget(Lvl3Btn);
    index++;

    // display quitBtn
    QuitBtn = new MenuButton("Quit");
    QuitBtn->move(xButton, yStartButton + index * (QuitBtn->height() + BTN_GAP));
    this->addWidget(QuitBtn);

    // Player Image
    playerImage = new QGraphicsPixmapItem();
    playerImage->setPos(1000, 400);
    this->addItem(playerImage);


    // Title
    QGraphicsTextItem* title = new QGraphicsTextItem();
    title->setPlainText(TITLE);
    QFont font = QFont("Agency FB", 100);
    font.setBold(true);
    title->setFont(font);
    title->setPos(900, 200);
    this->addItem(title);
}

Menu::~Menu()
{
    delete Lvl1Btn;
    delete Lvl2Btn;
    delete Lvl3Btn;
    delete QuitBtn;
}

void Menu::setMenuSprite(QString menuImage)
{
    QPixmap img = QPixmap(menuImage);
    img = img.scaled(400, 600);
    playerImage->setPixmap(img);
}

MenuButton* Menu::getLvl1Btn() const
{
    return Lvl1Btn;
}
MenuButton* Menu::getLvl2Btn() const
{
    return Lvl2Btn;
}
MenuButton* Menu::getLvl3Btn() const
{
    return Lvl3Btn;
}

MenuButton* Menu::getQuitBtn() const
{
    return QuitBtn;
}
