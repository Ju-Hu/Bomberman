#ifndef BOMBERMAN_H
#define BOMBERMAN_H

//#include <QtWidgets/QMainWindow>
//#include <qsplashscreen.h>      //Screen beim Boot
//#include <QTimer>
//#include <QGraphicsView>
//#include <Qlist>
//#include <qscrollbar.h>
//
//#include <QSignalMapper>
//#include <QApplication>
//#include <QGraphicsProxyWidget>
//#include <QGraphicsPixmapItem>
//#include <QGraphicsScene>
//#include <QObject>
//#include <QLabel>
//#include <QKeyEvent>
//#include <QPainter>   
//#include <fstream>
//#include <string>
//#include <regex>
//#include <iostream>
//
//
//#include <QMediaPlayer>         //Musik
//#include <QMediaPlaylist>
//#include <QSoundEffect>         //Soundeffekt

#include "config.h"
#include "menu.h"
#include "pause.h"
#include "sound.h"
#include "map.h"
#include "credits.h"

class Bomberman : public QGraphicsView
{
    Q_OBJECT

public:
    Bomberman();
    ~Bomberman();

    void openGame();

    void openPause();

    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);


    bool leftKey1 = false;
    bool rightKey1 = false;
    bool upKey1 = false;
    bool downKey1 = false;
    bool leftKey2 = false;
    bool rightKey2 = false;
    bool upKey2 = false;
    bool downKey2 = false;
    int StatusPlayer1 = 0;
    int StatusPlayer2 = 0;


    void resizeEvent(QResizeEvent* event);

    void openCredits();

public slots:

    void closeCredits();
    void closePause();

    void openMenu();

    void quitApp();

    //void setVolume();

    void clicked1();

    void clicked2();

    void clicked3();

    void animate();

    void refresh();

signals:
    void playSound(QString);
    //void setVolume(int);

private:

    QGraphicsScene* levelScene;

    Credits* creditsMenu;

    Menu* menuScene;

    Pause* pauseMenu;

    bool paused;

    enum gameState { Paused, InMenu, InGame };

    gameState Status;

    Sound* soundManager;

    QTimer* refreshTimer;

    QTimer* animationTimer;

    int anim = 0;

    Map *map;
};

#endif