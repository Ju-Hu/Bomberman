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
#include "victory.h"
#include "editor.h"


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

    int player1Speed = PLAYER_SPEED;
    int player2Speed = PLAYER_SPEED;

    bool leftKey1 = false;
    bool rightKey1 = false;
    bool upKey1 = false;
    bool downKey1 = false;
    bool leftKey2 = false;
    bool rightKey2 = false;
    bool upKey2 = false;
    bool downKey2 = false;
    bool bombKey1old = false;
    bool bombKey2old = false;

    bool bombMerker1 = false;
    bool bombMerker2 = false;
    bool cBombMerker1 = false;
    bool cBombMerker2 = false;

    bool xM1 = false;
    bool xM2 = false;
    bool xP1 = false;
    bool xP2 = false;
    bool yM1 = false;
    bool yM2 = false;
    bool yP1 = false;
    bool yP2 = false;

    int b1cnt =0;
    int b2cnt =0;
    int f1cnt = 0;
    int f2cnt = 0;
    int s1cnt = 0;
    int s2cnt = 0;

    int bombCnt1 = 0;
    int bombCnt2 = 0;

    bool bombItem1 = false;
    bool bombItem2 = false;

    bool flameItem1 = false;
    bool flameItem2 = false;

    bool speedItem1 = false;
    bool speedItem2 = false;

    int StatusPlayer1 =0;
    int StatusPlayer2 = 0;

    int editStatus = 0;

    int playerWon = 0;

    void resizeEvent(QResizeEvent* event);

    void openCredits();

    void openVictory();   


    void Flame(int x, int y);
    void FlameRemove(int x, int y);


public slots:

    void closeCredits();
    void closePause();
    void closeVictory();

    void openMenu();
    void openEditor();
    void quitApp();

    //void setVolume();

    void clicked1();

    void clicked2();

    void clicked3();

    void animate();

    void second();

    void refresh();

    void clickedEdit(int btnIndex);

    void loadEdit1();
    void loadEdit2();
    void loadEdit3();
    void loadEdit4();

    void saveEdit1();
    void saveEdit2();
    void saveEdit3();


signals:
    void playSound(QString);
    //void setVolume(int);

private:

    QGraphicsScene* levelScene;

    Credits* creditsMenu;

    Menu* menuScene;

    Editor* editorScene;

    Pause* pauseMenu;

    Victory* victoryMenu;

    bool paused;

    enum gameState { Paused, InMenu, InGame };

    gameState Status;

    Sound* soundManager;

    QTimer* refreshTimer;

    QTimer* animationTimer;

    QTimer* secTimer;

    QSignalMapper* buttonEditorMapper;

    int anim = 0;
    int standAnim = 0;

    Map *map;


};

#endif