// Game engine
#include "Bomberman.h"

//test
//// init windowsize
//int windowWidth = WINDOW_WIDTH;
//int windowHeight = WINDOW_HEIGHT;

Bomberman::Bomberman()
{
    windowWidth = WINDOW_WIDTH;
    windowHeight = WINDOW_HEIGHT;

    setWindowTitle(TITLE);

    // init szene
    levelScene = new QGraphicsScene();


    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // init Sound
    soundManager = new Sound();
    connect(this, &Bomberman::playSound, soundManager, &Sound::playSound);

    // init Timer

    //refreshTimer = new QTimer(this);
    //connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    //refreshTimer->start(1000 / FPS);
    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animationTimer->start(500);
    
    // init map
    map = new Map();
   
    // init main menu
    menuScene = new Menu();

    connect(menuScene->getLvl1Btn(), SIGNAL(clicked()), this, SLOT(clicked1()));
    connect(menuScene->getLvl2Btn(), SIGNAL(clicked()), this, SLOT(clicked2()));
    connect(menuScene->getLvl3Btn(), SIGNAL(clicked()), this, SLOT(clicked3()));

    //connect(buttonMenuMapper, SIGNAL(mapped(QString)), this, SLOT(loadMap(QString)));
    // link quit button in menu
    connect(menuScene->getQuitBtn(), SIGNAL(clicked()), this, SLOT(quitApp()));

    // init pause menu
    pauseMenu = new Pause();
    connect(pauseMenu->getContinueBtn(), SIGNAL(clicked()), this, SLOT(closePause()));
    connect(pauseMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));
    paused = false;

    creditsMenu = new Credits();

    //openMenu();
    //openGame();

    //showFullScreen();
}

Bomberman::~Bomberman()
{
    //animationTimer->stop();
    //delete animationTimer;
    refreshTimer->stop();
    delete refreshTimer;
    delete menuScene;
    delete pauseMenu;
    delete creditsMenu;
    delete soundManager;
}

void Bomberman::keyPressEvent(QKeyEvent* event)
{
    //--- Pfeil-Tasten ---
    if (event->key() == Qt::Key_Left) {
        leftKey = true;
    }

    if (event->key() == Qt::Key_Right) {
        rightKey = true;
    }

    if (event->key() == Qt::Key_Up) {
        upKey = true;
    }
    if (event->key() == Qt::Key_Down) {
        downKey = true;
    }
    if (event->key() == Qt::Key_Escape) {
        if (scene() == levelScene) {
            if (pauseMenu->scene() == levelScene)
                closePause();
            else
                openPause();
        }
        if (scene() == menuScene) {
            if (creditsMenu->scene() == menuScene)
                closeCredits();
            else
                openCredits();

        }
    }
    if (event->key() == Qt::Key_F11) {
        if (isFullScreen())
            showNormal();
        else
            showFullScreen();
    }


}

void Bomberman::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left) {
        leftKey = false;
    }
    if (event->key() == Qt::Key_Right) {
        rightKey = false;
    }
    if (event->key() == Qt::Key_Up) {
        upKey = false;
    }
    if (event->key() == Qt::Key_Down) {
        downKey = false;
    }
}

void Bomberman::openMenu()
{
    if (paused == true)
        closePause();

    paused = true;
    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timers
    /*Animtimer->stop();
    refreshTimer->stop();*/
    menuScene->removeItem(creditsMenu);
    // replace scene by menu scene
    setScene(menuScene);

    //menu music
    emit playSound("stopMusic");
    emit playSound("menu");
}

void Bomberman::clicked1()
{
    emit playSound("click");
    emit playSound("stopMusic");
    emit playSound("map1");
    map->generateMap1();
    for (int c = 0; c < COLUMN; c++) {
        for (int r = 0; r < ROW; r++) {
            levelScene->addItem(map->field[c][r]);
        }
    }
    openGame();
}

void Bomberman::clicked2()
{
    emit playSound("click");
    emit playSound("stopMusic");
    emit playSound("map2");
}

void Bomberman::clicked3()
{
    emit playSound("click");
    emit playSound("stopMusic");
    emit playSound("map3");
}

void Bomberman::quitApp()
{
    emit playSound("click");
    QTimer::singleShot(500, this, SLOT(close()));
}

void Bomberman::openGame()
{
    // hide mouse cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // start timer
    
    setScene(levelScene);
    paused = false;
}

void Bomberman::openPause()
{
    emit playSound("click");
    emit playSound("startPauseMusic");

    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timer
    paused = true;

    levelScene->addItem(pauseMenu);
    levelScene->addWidget(pauseMenu->getContinueBtn());
    levelScene->addWidget(pauseMenu->getBackMenuBtn());
}

void Bomberman::closePause()
{
    emit playSound("click");
    emit playSound("stopPauseMusic");

    // hide mouse cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // restart timers
    paused = false;

    // remove pause component from scene
    levelScene->removeItem(pauseMenu);
    levelScene->removeItem(pauseMenu->getBackMenuBtn()->graphicsProxyWidget());
    levelScene->removeItem(pauseMenu->getContinueBtn()->graphicsProxyWidget());
    // reset proxy
    pauseMenu->getBackMenuBtn()->graphicsProxyWidget()->setWidget(NULL);
    pauseMenu->getContinueBtn()->graphicsProxyWidget()->setWidget(NULL);
}

void Bomberman::openCredits()
{
    emit playSound("click");
    emit playSound("startPauseMusic");
    QApplication::setOverrideCursor(Qt::BlankCursor);
    menuScene->removeItem(menuScene->getLvl1Btn()->graphicsProxyWidget());
    menuScene->removeItem(menuScene->getLvl2Btn()->graphicsProxyWidget());
    menuScene->removeItem(menuScene->getLvl3Btn()->graphicsProxyWidget());
    menuScene->removeItem(menuScene->getQuitBtn()->graphicsProxyWidget());
    menuScene->getLvl1Btn()->graphicsProxyWidget()->setWidget(NULL);
    menuScene->getLvl2Btn()->graphicsProxyWidget()->setWidget(NULL);
    menuScene->getLvl3Btn()->graphicsProxyWidget()->setWidget(NULL);
    menuScene->getQuitBtn()->graphicsProxyWidget()->setWidget(NULL);
    
    menuScene->addItem(creditsMenu);
}

void Bomberman::closeCredits()
{
    emit playSound("click");
    emit playSound("stopPauseMusic");
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    menuScene->addWidget(menuScene->getLvl1Btn());
    menuScene->addWidget(menuScene->getLvl2Btn());
    menuScene->addWidget(menuScene->getLvl3Btn());
    menuScene->addWidget(menuScene->getQuitBtn());
    menuScene->removeItem(creditsMenu);
}

void Bomberman::animate()
{
    if (anim == 0) 
    {
        menuScene->setMenuSprite("images/player/2.png");
        anim = 1;
    }
    else if (anim == 1)
    {
        menuScene->setMenuSprite("images/player/1.png");
        anim = 0;
    }

}


void Bomberman::refresh()
{


}