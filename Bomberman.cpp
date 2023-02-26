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
            levelScene->addItem(map->Field[c][r]);
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
            levelScene->addItem(map->Field[c][r]);
        }
    }
    levelScene->addItem(map->player1);
    levelScene->addItem(map->player2);
    openGame();

}

void Bomberman::clicked3()
{
    emit playSound("click");
    emit playSound("stopMusic");
    emit playSound("map3");
    levelScene->clear();
    map->generateMap3();
    for (int c = 0; c < COLUMN; c++) {
        for (int r = 0; r < ROW; r++) {
            levelScene->addItem(map->Field[c][r]);
        }
    }
    levelScene->addItem(map->player1);
    levelScene->addItem(map->player2);

    openGame();
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
    if (Status == InGame) {
        switch (StatusPlayer1)
        {
            case 1:
                if (anim == 0) {
                    map->player1->setPixmap(map->Player1Pix1up1);
                }
                else if (anim == 1) {
                    map->player1->setPixmap(map->Player1Pix1up2);
                }break;
            case 2:
                if (anim == 0) {
                    map->player1->setPixmap(map->Player1Pix1ri1);
                }
                else if (anim == 1) {
                    map->player1->setPixmap(map->Player1Pix1ri2);
                }break;
            case 3:
                if (anim == 0) {
                    map->player1->setPixmap(map->Player1Pix1dw1);
                }
                else if (anim == 1) {
                    map->player1->setPixmap(map->Player1Pix1dw2);
                }break;
            case 4:       
                if (anim == 0) {
                map->player1->setPixmap(map->Player1Pix1lf1);
                }
                else if (anim == 1) {
                map->player1->setPixmap(map->Player1Pix1lf2);
                }break;
            default:       
                if (anim == 0){
                map->player1->setPixmap(map->Player1Pix1st1);
                }
                else if (anim == 1){
                map->player1->setPixmap(map->Player1Pix1st2);
                }break;
        }

        switch (StatusPlayer2)
        {
        case 1:
            if (anim == 0) {
                map->player2->setPixmap(map->Player2Pix1up1);
            }
            else if (anim == 1) {
                map->player2->setPixmap(map->Player2Pix1up2);
            }break;
        case 2:
            if (anim == 0) {
                map->player2->setPixmap(map->Player2Pix1ri1);
            }
            else if (anim == 1) {
                map->player2->setPixmap(map->Player2Pix1ri2);
            }break;
        case 3:
            if (anim == 0) {
                map->player2->setPixmap(map->Player2Pix1dw1);
            }
            else if (anim == 1) {
                map->player2->setPixmap(map->Player2Pix1dw2);
            }break;
        case 4:
            if (anim == 0) {
                map->player2->setPixmap(map->Player2Pix1lf1);
            }
            else if (anim == 1) {
                map->player2->setPixmap(map->Player2Pix1lf2);
            }break;
        default:
            if (anim == 0) {
                map->player2->setPixmap(map->Player2Pix1st1);
            }
            else if (anim == 1) {
                map->player2->setPixmap(map->Player2Pix1st2);
            }break;
        }
    }
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
        bool upStop1 = false;
        bool downStop1 = false;
        bool leftStop1 = false;
        bool rightStop1 = false;
        bool upStop2 = false;
        bool downStop2 = false;
        bool leftStop2 = false;
        bool rightStop2 = false;

        //Autocorrection Player 1
        if (!(lCorPlayer1 || rCorPlayer1) 
                &&((yPlayer1 % BLOCK_SIZE) <= deadspot
                    &&(yPlayer1 % BLOCK_SIZE) > 0) 
                        &&(leftKey1 || rightKey1)
                            &&!downKey1)            { uCorPlayer1 = true; }
        else
        { uCorPlayer1 = false; }

        if (!(lCorPlayer1 || rCorPlayer1) 
                &&((yPlayer1 % BLOCK_SIZE) < BLOCK_SIZE 
                    &&(yPlayer1 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) 
                        &&(leftKey1 || rightKey1)
                            &&!upKey1)              { dCorPlayer1 = true; }
        else 
        { dCorPlayer1 = false; }

        if (!(uCorPlayer1 || dCorPlayer1) 
                &&((xPlayer1 % BLOCK_SIZE) <= deadspot 
                    &&(xPlayer1 % BLOCK_SIZE) > 0) 
                        &&(upKey1 || downKey1)
                            &&!rightKey1)           { lCorPlayer1 = true; }
        else 
        { lCorPlayer1 = false; }

        if (!(uCorPlayer1 || dCorPlayer1)
                &&((xPlayer1 % BLOCK_SIZE) < BLOCK_SIZE 
                    &&(xPlayer1 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) 
                        &&(upKey1 || downKey1)
                            &&!leftKey1)            { rCorPlayer1 = true; }
        else 
        { rCorPlayer1 = false; }

        //Autocorrection Player 2
        if (!(lCorPlayer2 || rCorPlayer2) 
                &&((yPlayer2 % BLOCK_SIZE) <= deadspot 
                    &&(yPlayer2 % BLOCK_SIZE) > 0) 
                        &&(leftKey2 || rightKey2) 
                            &&!downKey2)            { uCorPlayer2 = true; }
        else 
        { uCorPlayer2 = false; }

        if (!(lCorPlayer2 || rCorPlayer2) 
                &&((yPlayer2 % BLOCK_SIZE) < BLOCK_SIZE 
                    &&(yPlayer2 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) 
                        &&(leftKey2 || rightKey2) 
                            &&!upKey2)              { dCorPlayer2 = true; }
        else 
        { dCorPlayer2 = false; }

        if (!(uCorPlayer2 || dCorPlayer2) 
                &&((xPlayer2 % BLOCK_SIZE) <= deadspot 
                    &&(xPlayer2 % BLOCK_SIZE) > 0) 
                        &&(upKey2 || downKey2) 
                            &&!rightKey2)           { lCorPlayer2 = true; }
        else 
        { lCorPlayer2 = false; }

        if (!(uCorPlayer2 || dCorPlayer2) 
            &&((xPlayer2 % BLOCK_SIZE) < BLOCK_SIZE 
                &&(xPlayer2 % BLOCK_SIZE) >= BLOCK_SIZE - deadspot) 
                    &&(upKey2 || downKey2) 
                        &&!leftKey1)            { rCorPlayer2 = true; }
        else 
        { rCorPlayer2 = false; }



        // Movment Obstacles avoidens Player1
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE)      / BLOCK_SIZE)]->st == 1) { downStop1 = true;}
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer1 - PLAYER_SPEED)    / BLOCK_SIZE)]->st == 1) { upStop1 = true;}
        if (map->Field[int((xPlayer1 + BLOCK_SIZE)      / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 1) { rightStop1 = true;}
        if (map->Field[int((xPlayer1 - PLAYER_SPEED)    / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 1) { leftStop1 = true;}
            
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE)      / BLOCK_SIZE)]->st == 2) { downStop1 = true;}
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer1 - PLAYER_SPEED)    / BLOCK_SIZE)]->st == 2) { upStop1 = true;}
        if (map->Field[int((xPlayer1 + BLOCK_SIZE)      / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 2) { rightStop1 = true;}
        if (map->Field[int((xPlayer1 - PLAYER_SPEED)    / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 2) { leftStop1 = true;}

        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE)      / BLOCK_SIZE)]->st == 8) { downStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer1 - PLAYER_SPEED)    / BLOCK_SIZE)]->st == 8) { upStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE)      / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 8) { rightStop1 = true; }
        if (map->Field[int((xPlayer1 - PLAYER_SPEED)    / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 8) { leftStop1 = true; }

        // Movment Obstacles avoidens Player 2
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE)      / BLOCK_SIZE)]->st == 1) { downStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer2 - PLAYER_SPEED)    / BLOCK_SIZE)]->st == 1) { upStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE)      / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 1) { rightStop2 = true; }
        if (map->Field[int((xPlayer2 - PLAYER_SPEED)    / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 1) { leftStop2 = true; }

        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE)      / BLOCK_SIZE)]->st == 2) { downStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer2 - PLAYER_SPEED)    / BLOCK_SIZE)]->st == 2) { upStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE)      / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 2) { rightStop2 = true; }
        if (map->Field[int((xPlayer2 - PLAYER_SPEED)    / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 2) { leftStop2 = true; }

        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE)      / BLOCK_SIZE)]->st == 8) { downStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)][int((yPlayer2 - PLAYER_SPEED)    / BLOCK_SIZE)]->st == 8) { upStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE)      / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 8) { rightStop2 = true; }
        if (map->Field[int((xPlayer2 - PLAYER_SPEED)    / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2)  / BLOCK_SIZE)]->st == 8) { leftStop2 = true; }


        //old Collision detection
        {//qDebug() << collidingP1[i]->x() << xPlayer1<< leftStop1;
        //qDebug() << leftStop1;
        //--------------Movment with Collision---------------------//
            //QList<QGraphicsItem*> collidingP1 = levelScene->collidingItems(map->player1);

            //for (int i = 0, n = collidingP1.size(); i < n; ++i) {
            //    if (typeid(*(collidingP1[i])) == typeid(Stein) ||
            //        typeid(*(collidingP1[i])) == typeid(Kiste))
            //    {
            //        if (!collidingP1.isEmpty()) {
            //            if (yPlayer1 + BLOCK_SIZE / 2 > collidingP1[i]->y()) { upStop1 = true; }
            //            if (yPlayer1 + BLOCK_SIZE / 2 < collidingP1[i]->y()) { downStop1 = true; }
            //            if (xPlayer1 + BLOCK_SIZE / 2 > collidingP1[i]->x()) { leftStop1 = true; }
            //            if (xPlayer1 + BLOCK_SIZE / 2 < collidingP1[i]->x()) { rightStop1 = true; }
            //        }
            //    }
            //    //---------------------------------------------------------//

            //    if (typeid(*(collidingP1[i])) == typeid(Bombe)) {
            //        if (!collidingP1.isEmpty()) {
            //            int y = int(collidingP1[i]->y() / BLOCK_SIZE);
            //            int x = int(collidingP1[i]->x() / BLOCK_SIZE);
            //            int z = map->BoField[x][y]->st;
            //            qDebug() << z;

            //            //levelScene->removeItem(collidingP1[i]);
            //        }
            //    }

            //    if (typeid(*(collidingP1[i])) == typeid(Flame)) {
            //        if (!collidingP1.isEmpty()) {
            //            // Tot oder Leben Abziehen
            //            // Flammen aufrufen
            //        }
            //    }

            //    if (typeid(*(collidingP1[i])) == typeid(Item)) {
            //        if (!collidingP1.isEmpty()) {
            //            int z = map->ItField[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st;
            //            qDebug() << z;
            //            // Tot oder Leben Abziehen
            //            // Flammen aufrufen
            //        }
            //    }

            //}


            //Collision
            //QList<QGraphicsItem*> colliding_items = levelScene->collidingItems(map->player1);
            //for (int i = 0, n = colliding_items.size(); i < n; ++i) {
            //    if (typeid(*(colliding_items[i])) == typeid(clBlock)) {
            //        if (!colliding_items.isEmpty()) {
            //            qDebug() << colliding_items[i]->x()/BLOCK_SIZE <<colliding_items[i]->y() / BLOCK_SIZE << "Stein";




        }




        //Movement Player 1
        if ((!upStop1 
                && upKey1 == true 
                    && (xPlayer1 % BLOCK_SIZE) == 0 || uCorPlayer1) 
                        && map->player1->y() >= PLAYER_SPEED) 
        {
            map->player1->moveBy(0, -PLAYER_SPEED);
            StatusPlayer1 = 1;
        }

        if ((!downStop1&& downKey1 == true && (xPlayer1 % BLOCK_SIZE == 0) || dCorPlayer1) && (map->player1->y() <= MAP_HEIGHT - BLOCK_SIZE- PLAYER_SPEED)) {
            map->player1->moveBy(0, PLAYER_SPEED);
            StatusPlayer1 = 3;
        }
        if ((!leftStop1 && leftKey1 == true && (yPlayer1 % BLOCK_SIZE) == 0 || lCorPlayer1) && map->player1->x() >= PLAYER_SPEED) {
            map->player1->moveBy(-PLAYER_SPEED, 0);
            StatusPlayer1 = 4;

        }
        if ((!rightStop1 && rightKey1 == true && (yPlayer1 % BLOCK_SIZE) == 0 || rCorPlayer1) && (map->player1->x() <= MAP_WIDTH - BLOCK_SIZE- PLAYER_SPEED)) {
            map->player1->moveBy(PLAYER_SPEED, 0);
            StatusPlayer1 = 2;

        }
        if (!upKey1 && !downKey1 && !rightKey1 && !leftKey1) {
            StatusPlayer1 = 0;
        }

        //Movement Player 2
        if ((!upStop2 && upKey2 == true && (xPlayer2 % BLOCK_SIZE) == 0 || uCorPlayer2) && map->player2->y() >= PLAYER_SPEED) {
            map->player2->moveBy(0, -PLAYER_SPEED);
            StatusPlayer2 = 1;
        }
        if ((!downStop2 && downKey2 == true && (xPlayer2 % BLOCK_SIZE == 0) || dCorPlayer2) && (map->player2->y() <= MAP_HEIGHT - BLOCK_SIZE - PLAYER_SPEED)) {
            map->player2->moveBy(0, PLAYER_SPEED);
            StatusPlayer2 = 3;
        }
        if ((!leftStop2 && leftKey2 == true && (yPlayer2 % BLOCK_SIZE) == 0 || lCorPlayer2) && map->player2->x() >= PLAYER_SPEED) {
            map->player2->moveBy(-PLAYER_SPEED, 0);
            StatusPlayer2 = 4;
        }
        if ((!rightStop2 && rightKey2 == true && (yPlayer2 % BLOCK_SIZE) == 0 || rCorPlayer2) && (map->player2->x() <= MAP_WIDTH - BLOCK_SIZE - PLAYER_SPEED)) {
            map->player2->moveBy(PLAYER_SPEED, 0);
            StatusPlayer2 = 2;
        }
        if (!upKey2 && !downKey2 && !rightKey2 && !leftKey2) {
            StatusPlayer2 = 0; }


        //----------Item detection Player1----------------------------//

        QList<QGraphicsItem*> collidingP1 = levelScene->collidingItems(map->player1);

        for (int i = 0, n = collidingP1.size(); i < n; ++i) {
            if (typeid(*(collidingP1[i])) == typeid(clBlock))
            {
                if (!collidingP1.isEmpty()) {
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 9){ //Flamme
                        qDebug() << "Flamme";
                        // Tot oder Leben Abziehen
                        // Flammen aufrufen
                    }
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 3) { //Item1
                        
                        levelScene->removeItem(collidingP1[i]);
                    }
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 4) { //Item2

                        levelScene->removeItem(collidingP1[i]);
                    }
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 5) { //Item3
                        
                        levelScene->removeItem(collidingP1[i]);
                    }
                }
            }
        }
        //----------Item detection Player2----------------------------//

        QList<QGraphicsItem*> collidingP2 = levelScene->collidingItems(map->player2);

        for (int i = 0, n = collidingP2.size(); i < n; ++i) {
            if (typeid(*(collidingP2[i])) == typeid(clBlock))
            {
                if (!collidingP2.isEmpty()) {
                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 9) { //Flamme
                        qDebug() << "Flamme";
                        // Tot oder Leben Abziehen
                        // Flammen aufrufen
                    }
                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 3) { //Item1

                        levelScene->removeItem(collidingP2[i]);
                    }
                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 4) { //Item2

                        levelScene->removeItem(collidingP2[i]);
                    }
                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 5) { //Item3

                        levelScene->removeItem(collidingP2[i]);
                    }
                }
            }
        }
        


     }

       
    //refresh Volume
     if (scene() == menuScene)
      {
        soundManager->setVolume(menuScene->getVolume());
      }

    
}


   

