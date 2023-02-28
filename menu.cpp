#include "menu.h"

//#include <QStyleHints>
Menu::Menu() : QGraphicsScene()
{
    int xButton = 200;
    int yStartButton = 100;
    // Create window scene with background
    this->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    QImage background = QImage("images/backgrounds/background_menu.png");
    background = background.scaled(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setBackgroundBrush(background);

    //// Display levels buttons
    int index = 0;

    //volume
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setStyleSheet(
        "QSlider::groove:horizontal { "
        "border: none; "
        "height: 20px; "
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4); "
        "margin: 2px 0; "
        "} "
        "QSlider::handle:horizontal { "
        "image: url(images/sound.png);"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f); "
        "border: 1px solid #5c5c5c; "
        "width: 30px; "
        "margin: -2px 0px; "
        "} "
        "QSlider::sub-page{background: rgb(164, 192, 2);}"
        "QSlider::add-page{background: rgb(70, 70, 70);}"
        );
    volumeSlider->setMinimumWidth(400);
    volumeSlider->setRange(0, 10);
    volumeSlider->setValue(5);
    volumeSlider->move(xButton, yStartButton + BTN_GAP);
    this->addWidget(volumeSlider);
    index++;

    // LVL1 Btn
    Lvl1Btn = new MenuButton("Level 1");
    Lvl1Btn->move(xButton, yStartButton + index * (Lvl1Btn->height() + BTN_GAP));
    Lvl1Btn->setStyleSheet("border-image:url(images/menubutton.png);");
    this->addWidget(Lvl1Btn);
    index++;

    // LVL2 Btn
    Lvl2Btn = new MenuButton("Level 2");
    Lvl2Btn->move(xButton, yStartButton + index * (Lvl2Btn->height() + BTN_GAP));
    Lvl2Btn->setStyleSheet("border-image:url(images/menubutton.png);");
    this->addWidget(Lvl2Btn);
    index++;

    // LVL3 Btn
    Lvl3Btn = new MenuButton("Level 3");
    Lvl3Btn->move(xButton, yStartButton + index * (Lvl3Btn->height() + BTN_GAP));
    Lvl3Btn->setStyleSheet("border-image:url(images/menubutton.png);");
    this->addWidget(Lvl3Btn);
    index++;

    // Editor Btn
    EditBtn = new MenuButton("Editor");
    EditBtn->move(xButton, yStartButton + index * (EditBtn->height() + BTN_GAP));
    EditBtn->setStyleSheet("border-image:url(images/menubutton.png);");
    this->addWidget(EditBtn);
    index++;

    // display quitBtn
    QuitBtn = new MenuButton("Quit");
    QuitBtn->move(xButton, yStartButton + index * (QuitBtn->height() + BTN_GAP));
    QuitBtn->setStyleSheet("border-image:url(images/quitbutton.png);");
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
    title->setPos(940, 200);
    this->addItem(title);

    // Fullscreen Text
    QGraphicsTextItem* f11 = new QGraphicsTextItem();
    f11->setPlainText("F11 = Fullscreen\nESC = Credits");
    QFont font2 = QFont("Agency FB", 20);
    font2.setBold(true);
    f11->setFont(font2);
    f11->setPos(0, 0);
    this->addItem(f11);
}

Menu::~Menu()
{
    delete volumeSlider;
    delete Lvl1Btn;
    delete Lvl2Btn;
    delete Lvl3Btn;
    delete EditBtn;
    delete QuitBtn;
}

void Menu::setMenuSprite(QString menuImage)
{
    QPixmap img = QPixmap(menuImage);
    img = img.scaled(400, 600);
    playerImage->setPixmap(img);
}

int Menu::getVolume()
{
    //qDebug() << "bin in getVolume";
    //qDebug() << "get Volume " << volumeSlider->value();
    return volumeSlider->value();
  
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
MenuButton* Menu::getEditBtn() const
{
    return EditBtn;
}
MenuButton* Menu::getQuitBtn() const
{
    return QuitBtn;
}
