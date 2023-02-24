// Game engine
#include "Bomberman.h"

//test
//// init windowsize
//int windowWidth = WINDOW_WIDTH;
//int windowHeight = WINDOW_HEIGHT;

Bomberman::Bomberman()
{
    setWindowTitle(TITLE);

    // init szene
    levelScene = new QGraphicsScene();
    QImage backgroundMap = QImage("images/backgrounds/background_map.png");
    //background = background.scaled(WINDOW_HEIGHT, WINDOW_WIDTH);
    levelScene->setBackgroundBrush(backgroundMap);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // init Sound
    soundManager = new Sound();
    connect(this, &Bomberman::playSound, soundManager, &Sound::playSound);

   
    // init map
    map = new Map();
   

    // init Timer

    refreshTimer = new QTimer(this);
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    refreshTimer->start(1000 / FPS);
    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animationTimer->start(500);
    
 
  
   
    // init main menu
    menuScene = new Menu();

    //connect(menuScene, &Menu::getVolume, soundManager, &Sound::setVolume);

    connect(menuScene->getLvl1Btn(), SIGNAL(clicked()), this, SLOT(clicked1()));
    connect(menuScene->getLvl2Btn(), SIGNAL(clicked()), this, SLOT(clicked2()));
    connect(menuScene->getLvl3Btn(), SIGNAL(clicked()), this, SLOT(clicked3()));
    //connect(menuScene->volumeSlider, SIGNAL(valueChanged()), soundManager, SLOT(setVolume())); //getVolume() //valueChanged()

    //connect(buttonMenuMapper, SIGNAL(mapped(QString)), this, SLOT(loadMap(QString)));
    // link quit button in menu
    connect(menuScene->getQuitBtn(), SIGNAL(clicked()), this, SLOT(quitApp()));

    // init pause menu
    pauseMenu = new Pause();
    connect(pauseMenu->getContinueBtn(), SIGNAL(clicked()), this, SLOT(closePause()));
    connect(pauseMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));
    paused = false;
    Status = Paused;

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
        leftKey1 = true;
    }

    if (event->key() == Qt::Key_Right ) {
        rightKey1 = true;
    }

    if (event->key() == Qt::Key_Up) {
        upKey1 = true;
    }
    if (event->key() == Qt::Key_Down) {
        downKey1 = true;
    }

    if (event->key() == Qt::Key_A ) {
        leftKey2 = true;
    }

    if (event->key() == Qt::Key_D ) {
        rightKey2 = true;
    }

    if (event->key() == Qt::Key_W ) {
        upKey2 = true;
    }
    if (event->key() == Qt::Key_S) {
        downKey2 = true;
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
        leftKey1 = false;
    }
    if (event->key() == Qt::Key_Right) {
        rightKey1 = false;
    }
    if (event->key() == Qt::Key_Up) {
        upKey1 = false;
    }
    if (event->key() == Qt::Key_Down) {
        downKey1 = false;
    }

    if (event->key() == Qt::Key_A) {
        leftKey2 = false;
    }
    if (event->key() == Qt::Key_D) {
        rightKey2 = false;
    }
    if (event->key() == Qt::Key_W) {
        upKey2 = false;
    }
    if (event->key() == Qt::Key_S) {
        downKey2 = false;
    }
}

void Bomberman::resizeEvent(QResizeEvent* event)
{
    qDebug() << "resize";
    /*if (levelScene)
        levelScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);*/
    // Scale the view to the new size
    QRect rect = QRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    fitInView(rect);
}

void Bomberman::openMenu()
{
    if (paused == true)
        closePause();

    paused = true;
    Status = InMenu;
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
    levelScene->clear();
    map->generateMap1();
    for (int c = 0; c < COLUMN; c++) {
        for (int r = 0; r < ROW; r++) {
            levelScene->addItem(map->field[c][r]);
        }
    }
    levelScene->addItem(map->player1);
    levelScene->addItem(map->player2);


    openGame();
}

void Bomberman::clicked2()
{
    emit playSound("click");
    emit playSound("stopMusic");
    emit playSound("map2");
    levelScene->clear();
    map->generateMap2();
    for (int c = 0; c < COLUMN; c++) {
        for (int r = 0; r < ROW; r++) {
            levelScene->addItem(map->field[c][r]);
        }
    }
    openGame();
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
Status = InGame;

}

void Bomberman::openPause()
{

    emit playSound("click");
    emit playSound("startPauseMusic");

    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timer
    paused = true;
    Status = Paused;

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
    Status = InGame;
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

    /*switch (StatusPlayer1)
    {
    case 1: map->player1->setPixmap(pxUp1Player1); 
            map->player1->setPixmap(pxUp2Player1);      break;

    case 2: map->player1->setPixmap(pxRight1Player1);
            map->player1->setPixmap(pxRight2Player1);   break;  

    case 3: map->player1->setPixmap(pxDown1Player1);
            map->player1->setPixmap(pxDown2Player1);    break;

    case 4: map->player1->setPixmap(pxLeft1Player1);
            map->player1->setPixmap(pxLeft2Player1);    break;

    case 5: map->player1->setPixmap(pxDeath1Player1);      break;

    default:    map->player1->setPixmap(pxStand1Player1);
                map->player1->setPixmap(pxStand2Player1); break; 
    }

    switch (StatusPlayer2)
    {
    case 1: map->player2->setPixmap(pxUp1Player2);
            map->player2->setPixmap(pxUp2Player2);      break;

    case 2: map->player2->setPixmap(pxRight1Player2);
            map->player2->setPixmap(pxRight2Player2);   break;

    case 3: map->player2->setPixmap(pxDown1Player2);
            map->player2->setPixmap(pxDown2Player2);    break;

    case 4: map->player2->setPixmap(pxLeft1Player2);
            map->player2->setPixmap(pxLeft2Player2);    break;

    case 5: map->player2->setPixmap(pxDeath1Player2);      break;

    default:    map->player2->setPixmap(pxStand1Player2);
                map->player2->setPixmap(pxStand2Player2); break;
    }*/

}


void Bomberman::refresh()
{

    if (Status == InGame) {

        int deadspot = 30;
        int xPlayer1 = map->player1->x();
        int yPlayer1 = map->player1->y();
        int xPlayer2 = map->player2->x();
        int yPlayer2 = map->player2->y();

        static bool uCorPlayer1;
        static bool dCorPlayer1;
        static bool lCorPlayer1;
        static bool rCorPlayer1;
        static bool uCorPlayer2;
        static bool dCorPlayer2;
        static bool lCorPlayer2;
        static bool rCorPlayer2;

        //Autocorrection Player 1
        if (!(lCorPlayer1 || rCorPlayer1) && ((yPlayer1 % BLOCK_SIZE) <= deadspot && (yPlayer1 % BLOCK_SIZE) > 0) && (leftKey1 || rightKey1)) { uCorPlayer1 = true; }
        else { uCorPlayer1 = false; }
        if (!(lCorPlayer1 || rCorPlayer1) && ((yPlayer1 % BLOCK_SIZE) < BLOCK_SIZE && (yPlayer1 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) && (leftKey1 || rightKey1)) { dCorPlayer1 = true; }
        else { dCorPlayer1 = false; }
        if (!(uCorPlayer1 || dCorPlayer1) && ((xPlayer1 % BLOCK_SIZE) <= deadspot && (xPlayer1 % BLOCK_SIZE) > 0) && (upKey1 || downKey1)) { lCorPlayer1 = true; }
        else { lCorPlayer1 = false; }
        if (!(uCorPlayer1 || dCorPlayer1) && ((xPlayer1 % BLOCK_SIZE) < BLOCK_SIZE && (xPlayer1 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) && (upKey1 || downKey1)) { rCorPlayer1 = true; }
        else { rCorPlayer1 = false; }

        //Autocorrection Player 2
        if (!(lCorPlayer2 || rCorPlayer2) && ((yPlayer2 % BLOCK_SIZE) <= deadspot && (yPlayer2 % BLOCK_SIZE) > 0) && (leftKey2 || rightKey2)) { uCorPlayer2 = true; }
        else { uCorPlayer2 = false; }
        if (!(lCorPlayer2 || rCorPlayer2) && ((yPlayer2 % BLOCK_SIZE) < BLOCK_SIZE && (yPlayer2 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) && (leftKey2 || rightKey2)) { dCorPlayer2 = true; }
        else { dCorPlayer2 = false; }
        if (!(uCorPlayer2 || dCorPlayer2) && ((xPlayer2 % BLOCK_SIZE) <= deadspot && (xPlayer2 % BLOCK_SIZE) > 0) && (upKey2 || downKey2)) { lCorPlayer2 = true; }
        else { lCorPlayer2 = false; }
        if (!(uCorPlayer2 || dCorPlayer2) && ((xPlayer2 % BLOCK_SIZE) < BLOCK_SIZE && (xPlayer2 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) && (upKey2 || downKey2)) { rCorPlayer2 = true; }
        else { rCorPlayer2 = false; }

        //Movement Player 1
        if (((upKey1 == true && (xPlayer1 % BLOCK_SIZE) == 0) || uCorPlayer1) && map->player1->y() >= 0) {
            map->player1->moveBy(0, -PLAYER_SPEED);
            StatusPlayer1 = 1;
        }
        if ((downKey1 == true && (xPlayer1 % BLOCK_SIZE == 0) || dCorPlayer1) && (map->player1->y() <= MAP_HEIGHT - BLOCK_SIZE)) {
            map->player1->moveBy(0, PLAYER_SPEED);
            StatusPlayer1 = 3;
        }
        if ((leftKey1 == true && (yPlayer1 % BLOCK_SIZE) == 0 || lCorPlayer1) && map->player1->x() >= 0) {
            map->player1->moveBy(-PLAYER_SPEED, 0);
            StatusPlayer1 = 4;
        }
        if ((rightKey1 == true && (yPlayer1 % BLOCK_SIZE) == 0 || rCorPlayer1) && (map->player1->x() <= MAP_WIDTH - BLOCK_SIZE)) {
            map->player1->moveBy(PLAYER_SPEED, 0);
            StatusPlayer1 = 2;
        }
        if (!upKey1 && !downKey1 && !rightKey1 && !leftKey1) { StatusPlayer1 = 0; }

        //Movement Player 2
        if (((upKey2 == true && (xPlayer2 % BLOCK_SIZE) == 0) || uCorPlayer2) && map->player2->y() >= 0) {
            map->player2->moveBy(0, -PLAYER_SPEED);
            StatusPlayer2 = 1;
        }
        if ((downKey2 == true && (xPlayer2 % BLOCK_SIZE == 0) || dCorPlayer2) && (map->player2->y() <= MAP_HEIGHT - BLOCK_SIZE)) {
            map->player2->moveBy(0, PLAYER_SPEED);
            StatusPlayer2 = 3;
        }
        if ((leftKey2 == true && (yPlayer2 % BLOCK_SIZE) == 0 || lCorPlayer2) && map->player2->x() >= 0) {
            map->player2->moveBy(-PLAYER_SPEED, 0);
            StatusPlayer2 = 4;
        }
        if ((rightKey2 == true && (yPlayer2 % BLOCK_SIZE) == 0 || rCorPlayer2) && (map->player2->x() <= MAP_WIDTH - BLOCK_SIZE)) {
            map->player2->moveBy(PLAYER_SPEED, 0);
            StatusPlayer2 = 2;
        }
        if (!upKey2 && !downKey2 && !rightKey2 && !leftKey2) { StatusPlayer2 = 0; }


        QList<QGraphicsItem*> colliding_items = levelScene->collidingItems(map->player1);
        for (int i = 0, n = colliding_items.size(); i < n; ++i) {
            if (typeid(*(colliding_items[i])) == typeid(clBlock)) {
                if (!colliding_items.isEmpty()) qDebug() << colliding_items;
            }
            if (typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)) {
                if (!colliding_items.isEmpty()) qDebug() << colliding_items;
            }
        }

     }

       
    //refresh Volume
     if (scene() == menuScene)
      {
        soundManager->setVolume(menuScene->getVolume());
      }

    
}


   

