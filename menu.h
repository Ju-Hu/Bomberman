#ifndef MENU_H
#define MENU_H
//#include <QObject>
#include "config.h"
#include "menubutton.h"
//#include "Bomberman.h"
//#include "player.h"
//#include "map.h"
//#include <QDebug>
//#include "element.h"

class Menu : public QGraphicsScene
{
public:
 
    Menu();
 
    ~Menu();

    MenuButton* getLvl1Btn() const;

    MenuButton* getLvl2Btn() const;

    MenuButton* getLvl3Btn() const;

    MenuButton* getEditBtn() const;

    MenuButton* getQuitBtn() const;

    void setMenuSprite(QString menuImage);

public slots:
    int getVolume();


private:

    QSlider* volumeSlider;

    MenuButton* Lvl1Btn;

    MenuButton* Lvl2Btn;

    MenuButton* Lvl3Btn;

    MenuButton* EditBtn;

    MenuButton* QuitBtn;

    QGraphicsPixmapItem* playerImage;

};

#endif