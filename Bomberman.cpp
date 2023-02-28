// Game engine
#include "Bomberman.h"


Bomberman::Bomberman()
{
    setWindowTitle(TITLE);

    // init szene
    levelScene = new QGraphicsScene();
    QImage backgroundMap = QImage("images/backgrounds/background_map.png");
    //backgroundMap = backgroundMap.scaled(WINDOW_HEIGHT/2, WINDOW_WIDTH/2);
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
    animationTimer->start(200);
    
    secTimer = new QTimer(this);
    connect(secTimer, SIGNAL(timeout()), this, SLOT(second()));
    secTimer->start(500);

    
 
  
   
    // init main menu
    menuScene = new Menu();

    connect(menuScene->getLvl1Btn(), SIGNAL(clicked()), this, SLOT(clicked1()));
    connect(menuScene->getLvl2Btn(), SIGNAL(clicked()), this, SLOT(clicked2()));
    connect(menuScene->getLvl3Btn(), SIGNAL(clicked()), this, SLOT(clicked3()));
    connect(menuScene->getEditBtn(), SIGNAL(clicked()), this, SLOT(openEditor()));
    connect(menuScene->getQuitBtn(), SIGNAL(clicked()), this, SLOT(quitApp()));

    // init Editor menu-----------------------------------------------------------------------------------------
    editorScene = new Editor();
    connect(editorScene->getMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));
    connect(editorScene->loadLvl1Btn(), SIGNAL(clicked()), this, SLOT(loadEdit1()));
    connect(editorScene->loadLvl2Btn(), SIGNAL(clicked()), this, SLOT(loadEdit2()));
    connect(editorScene->loadLvl3Btn(), SIGNAL(clicked()), this, SLOT(loadEdit3()));
    connect(editorScene->loadLvl4Btn(), SIGNAL(clicked()), this, SLOT(loadEdit4()));
    connect(editorScene->setLvl1Btn(), SIGNAL(clicked()), this, SLOT(saveEdit1()));
    connect(editorScene->setLvl2Btn(), SIGNAL(clicked()), this, SLOT(saveEdit2()));
    connect(editorScene->setLvl3Btn(), SIGNAL(clicked()), this, SLOT(saveEdit3()));

    buttonEditorMapper = new QSignalMapper(this);
    for (int r = 0; r < ROW;) {
        for (int c = 0; c < COLUMN; c++) {
            connect(editorScene->editField[c][r], SIGNAL(clicked()), buttonEditorMapper, SLOT(map()));
            buttonEditorMapper->setMapping(editorScene->editField[c][r], editorScene->editField[c][r]->btnID);
        }
        r++;
    }
    connect(buttonEditorMapper, SIGNAL(mapped(int)), this, SLOT(clickedEdit(int)));
    // -----------------------------------------------------------------------------------------------------------

    // init pause menu
    pauseMenu = new Pause();
    connect(pauseMenu->getContinueBtn(), SIGNAL(clicked()), this, SLOT(closePause()));
    connect(pauseMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));
    paused = false;
    Status = Paused;

    // init credits menu
    creditsMenu = new Credits();

    // init victory menu
    victoryMenu = new Victory();
    connect(victoryMenu->getBackMenuBtn2(), SIGNAL(clicked()), this, SLOT(openMenu()));
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
    if (event->key() == Qt::Key_Space) {
        //Bomb placement Player2
        if (scene() == levelScene && bombKey2old == false ) {
            bombKey2old = true;
            if (bombCnt2 < 1 ) {
                int x2 = map->player2->x();
                int y2 = map->player2->y();
                x2 = (int(x2 + BLOCK_SIZE / 2) / BLOCK_SIZE);
                y2 = (int(y2 + BLOCK_SIZE / 2) / BLOCK_SIZE);
                map->Field[x2][y2]->st = 8;
                map->Field[x2][y2]->setPixmap(Map().BombPix1);
                bombMerker2 = true;
                bombCnt2 += 6;
                if (flameItem2 == true) {
                    map->Field[x2][y2]->flame = true;
                }

            }
        }
    }
    if (event->key() == Qt::Key_Enter|| event->key() == Qt::Key_Return) {
        //Bomb placement Player1
        if (scene() == levelScene && bombKey1old == false) {
            bombKey1old = true;

            if (bombCnt1 < 1 ) {
                int x1 = map->player1->x();
                int y1 = map->player1->y();
                x1 = (int(x1 + BLOCK_SIZE / 2) / BLOCK_SIZE);
                y1 = (int(y1 + BLOCK_SIZE / 2) / BLOCK_SIZE);
                map->Field[x1][y1]->st = 8;
                map->Field[x1][y1]->setPixmap(Map().BombPix1);
                bombMerker1 = true;
                bombCnt1 += 6;
                if (flameItem1 == true) {
                    map->Field[x1][y1]->flame = true;
                }
            }
        }
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
    if (event->key() == Qt::Key_Space) {
        bombKey2old = false;
    }
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        bombKey1old = false;
    }
}

void Bomberman::resizeEvent(QResizeEvent* event)
{
    qDebug() << "resize";
    /*if (levelScene)
        levelScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);*/
    // Scale the view to the new size
    QRect rect = QRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    fitInView(rect, Qt::KeepAspectRatio);
}

void Bomberman::openMenu()
{
    if (pauseMenu->scene() == levelScene)
        closePause();
    if (victoryMenu->scene() == levelScene)
        closeVictory();
    if (scene() == editorScene)
        emit playSound("click");

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
    emit playSound("menu");
}

void Bomberman::clicked1()
{
    emit playSound("click");
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

    b1cnt = 0;
    b2cnt = 0;
    f1cnt = 0;
    f2cnt = 0;
    s1cnt = 0;
    s2cnt = 0;

    bombCnt1 = 0;
    bombCnt2 = 0;

    player1Speed = PLAYER_SPEED;
    player2Speed = PLAYER_SPEED;

    bombItem1 = false;
    bombItem2 = false;

    flameItem1 = false;
    flameItem2 = false;

    speedItem1 = false;
    speedItem2 = false;
    openGame();
}

void Bomberman::clicked2()
{
    emit playSound("click");
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

    b1cnt = 0;
    b2cnt = 0;
    f1cnt = 0;
    f2cnt = 0;
    s1cnt = 0;
    s2cnt = 0;

    player1Speed = PLAYER_SPEED;
    player2Speed = PLAYER_SPEED;

    bombCnt1 = 0;
    bombCnt2 = 0;

    bombItem1 = false;
    bombItem2 = false;

    flameItem1 = false;
    flameItem2 = false;

    speedItem1 = false;
    speedItem2 = false;
    openGame();

}

void Bomberman::clicked3()
{
    emit playSound("click");
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

    b1cnt = 0;
    b2cnt = 0;
    f1cnt = 0;
    f2cnt = 0;
    s1cnt = 0;
    s2cnt = 0;

    player1Speed = PLAYER_SPEED;
    player2Speed = PLAYER_SPEED;

    bombCnt1 = 0;
    bombCnt2 = 0;

    bombItem1 = false;
    bombItem2 = false;

    flameItem1 = false;
    flameItem2 = false;

    speedItem1 = false;
    speedItem2 = false;
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
    menuScene->removeItem(menuScene->getLvl1Btn()->graphicsProxyWidget());
    menuScene->removeItem(menuScene->getLvl2Btn()->graphicsProxyWidget());
    menuScene->removeItem(menuScene->getLvl3Btn()->graphicsProxyWidget());
    menuScene->removeItem(menuScene->getEditBtn()->graphicsProxyWidget());
    menuScene->removeItem(menuScene->getQuitBtn()->graphicsProxyWidget());
    menuScene->getLvl1Btn()->graphicsProxyWidget()->setWidget(NULL);
    menuScene->getLvl2Btn()->graphicsProxyWidget()->setWidget(NULL);
    menuScene->getLvl3Btn()->graphicsProxyWidget()->setWidget(NULL);
    menuScene->getEditBtn()->graphicsProxyWidget()->setWidget(NULL);
    menuScene->getQuitBtn()->graphicsProxyWidget()->setWidget(NULL);

    menuScene->addItem(creditsMenu);
}

void Bomberman::closeCredits()
{
    emit playSound("click");
    emit playSound("stopPauseMusic");
    menuScene->addWidget(menuScene->getLvl1Btn());
    menuScene->addWidget(menuScene->getLvl2Btn());
    menuScene->addWidget(menuScene->getLvl3Btn());
    menuScene->addWidget(menuScene->getEditBtn());
    menuScene->addWidget(menuScene->getQuitBtn());
    menuScene->removeItem(creditsMenu);
}

void Bomberman::openVictory()
{
    emit playSound("win");
    emit playSound("stopMusic");

    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timer
    paused = true;
    Status = Paused;
    if (playerWon == 1) { victoryMenu->title->setPlainText("   Blue\n  Wins!"); }
    if (playerWon == 2) { victoryMenu->title->setPlainText("  Green\n  Wins!"); }

    levelScene->addItem(victoryMenu);
    levelScene->addWidget(victoryMenu->getBackMenuBtn2());
}

void Bomberman::closeVictory()
{
    emit playSound("click");

    // hide mouse cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // remove pause component from scene
    playerWon = 0;
    levelScene->removeItem(victoryMenu);
    levelScene->removeItem(victoryMenu->getBackMenuBtn2()->graphicsProxyWidget());
    // reset proxy
    victoryMenu->getBackMenuBtn2()->graphicsProxyWidget()->setWidget(NULL);
}

// Editor--------------------------------------------------------------------------------------
void Bomberman::openEditor()
{
    emit playSound("click");
    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);


    // replace scene by Editor scene
    setScene(editorScene);
}

void Bomberman::clickedEdit(int btnIndex)
{
    emit playSound("click");
    for (int r = 0; r < ROW;) {
        for (int c = 0; c < COLUMN; c++) {
            if (editorScene->editField[c][r]->btnID == btnIndex)
            {
                editStatus = editorScene->editField[c][r]->st;
                editStatus++;
                if (editStatus <= 7)
                {
                    editorScene->editField[c][r]->text = QString::number(editStatus);
                    //editorScene->editField[c][r]->setText(editorScene->editField[c][r]->text);
                    editorScene->editField[c][r]->st = editStatus;
                    if (editorScene->editField[c][r]->st == 1) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/block3.png);"); }
                    if (editorScene->editField[c][r]->st == 2) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/block4.png);"); }
                    if (editorScene->editField[c][r]->st == 3) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/powerup1.png);"); }
                    if (editorScene->editField[c][r]->st == 4) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/powerup2.png);"); }
                    if (editorScene->editField[c][r]->st == 5) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/powerup3.png);"); }
                    if (editorScene->editField[c][r]->st == 6) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/player1.png);"); }
                    if (editorScene->editField[c][r]->st == 7) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/player2.png);"); }
                }
                if (editStatus == 8)
                {
                    editStatus = 0;
                    editorScene->editField[c][r]->text = QString::number(editStatus);
                    //editorScene->editField[c][r]->setText(editorScene->editField[c][r]->text);
                    editorScene->editField[c][r]->st = editStatus;
                    if (editorScene->editField[c][r]->st == 0) { editorScene->editField[c][r]->setStyleSheet("border-image:url(images/block0.png);"); }
                }
            }
        }
        r++;
    }
}
void Bomberman::loadEdit1()
{
    emit playSound("click");
    editorScene->loadEditor(1);
}
void Bomberman::loadEdit2()
{
    emit playSound("click");
    editorScene->loadEditor(2);
}
void Bomberman::loadEdit3()
{
    emit playSound("click");
    editorScene->loadEditor(3);
}
void Bomberman::loadEdit4()
{
    emit playSound("click");
    editorScene->loadEditor(4);
}
void Bomberman::saveEdit1()
{
    emit playSound("click");
    editorScene->saveEditor(1);
}
void Bomberman::saveEdit2()
{
    emit playSound("click");
    editorScene->saveEditor(2);
}
void Bomberman::saveEdit3()
{
    emit playSound("click");
    editorScene->saveEditor(3);
}


//----------------------------------------------------------------------------------------------------

void Bomberman::animate()
{
    if (standAnim == 0)
    {
        menuScene->setMenuSprite("images/player/player1/stop1.png");
        anim = 1;
        standAnim++;
    }
    else if (standAnim == 1)
    {
        anim = 0;
        standAnim++;
    }
    else if (standAnim == 2)
    {
        srand(time(NULL));
        if (rand() % 13 == 1) { menuScene->setMenuSprite("images/player/player1/stop4.png"); }
        else { menuScene->setMenuSprite("images/player/player1/stop2.png"); }
        anim = 1;
        standAnim++;
    }
    else if (standAnim == 3)
    {
        anim = 0;
        standAnim = 0;
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
                if (standAnim == 0){
                map->player1->setPixmap(map->Player1Pix1st1);
                }
                else if (standAnim == 1){
                map->player1->setPixmap(map->Player1Pix1st2);
                }
                else if (standAnim == 2) {
                map->player1->setPixmap(map->Player1Pix1st3);
                }
                else if (standAnim == 3) {
                map->player1->setPixmap(map->Player1Pix1st4);
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
            if (standAnim == 0) {
                map->player2->setPixmap(map->Player2Pix1st1);
            }
            else if (standAnim == 1) {
                map->player2->setPixmap(map->Player2Pix1st2);
            }
            else if (standAnim == 2) {
                map->player2->setPixmap(map->Player2Pix1st3);
            }
            else if (standAnim == 3) {
                map->player2->setPixmap(map->Player2Pix1st4);
            }break;
        }

    }
}

void Bomberman::second() 
{


    if (Status == InGame) {
       
        if (speedItem1 == true) { 
            player1Speed = PLAYER_SPEED + BOOST;
            s1cnt++;
            if (s1cnt > 12) {
                player1Speed = PLAYER_SPEED;
                speedItem1 = false;
                s1cnt = 0;
            }
        }
        if (speedItem2 == true) {
            player2Speed = PLAYER_SPEED + BOOST;
            s2cnt++;
            if (s2cnt > 12) {
                player2Speed = PLAYER_SPEED;
                speedItem2 = false;
                s2cnt = 0;
            }
        }
        if (bombItem1 == true) {
            b1cnt++;
            if (b1cnt > 12) {
                bombItem1 = false;
                b1cnt = 0;
            }
        }
        if (bombItem2 == true) {
            b2cnt++;
            if (b2cnt > 12) {
                bombItem2 = false;
                b2cnt = 0;
            }
        }
        if (flameItem1 == true) {
            f1cnt++;
            if (f1cnt > 12) {
                flameItem1 = false;
                f1cnt = 0;
            }
        }
        if (flameItem2 == true) {

            f2cnt++;
            if (f2cnt > 12) {
                flameItem2 = false;
                f2cnt = 0;
            }
        }


        if (bombCnt1 >0 ) {
            if (bombItem1 == true) { bombCnt1 -= 6; }
            else { bombCnt1 -= 1; }
        }
        if (bombCnt2 > 0) {
            if (bombItem2 == true) { bombCnt2 -= 6; }
            else { bombCnt2 -= 1; }
        }





        for (int c = 0; c < COLUMN; c++) {
            for (int r = 0; r < ROW; r++) {
                if (map->Field[c][r]->st == 0 && map->Field[c][r]->time > 0) {
                    map->Field[c][r]->time = 0;
                }
                if (map->Field[c][r]->st == 8) {
                    map->Field[c][r]->time = map->Field[c][r]->time +1;

                    if (map->Field[c][r]->time >= 6) {
                        map->Field[c][r]->time = map->Field[c][r]->time + 1;
                        Flame(c, r);
                    }
                }
                if (map->Field[c][r]->st == 9) {
                    map->Field[c][r]->time = map->Field[c][r]->time +1;
                    if (map->Field[c][r]->time >= 14) {
                        FlameRemove(c, r);
                       
                    }
                 
                }
            }
        }
    }
}

void Bomberman::Flame(int x, int y) {

    emit playSound("explosion");

    if (x - 1 >= 0) { xM1 = true; }
    else { xM1 = false; }
    if (x - 2 >= 0) { xM2 = true; }
    else { xM2 = false; }
    if (x + 1 < ROW) { xP1 = true; }
    else { xP1 = false; }
    if (x + 2 < ROW) { xP2 = true; }
    else { xP2 = false; }

    if (y - 1 >= 0) { yM1 = true; }
    else { yM1 = false; }
    if (y - 2 >= 0) { yM2 = true; }
    else { yM2 = false; }
    if (y + 1 < COLUMN) { yP1 = true; }
    else { yP1 = false; }
    if (y + 2 < COLUMN) { yP2 = true; }
    else { yP2 = false; }

    srand(time(NULL));

    if (map->Field[x][y]->st != 9) {
        map->Field[x][y]->st = 9;
        map->Field[x][y]->setPixmap(Map().FlamePix1);

    }
    if (xP1 == true) {
        if (map->Field[x + 1][y]->st != 1 && map->Field[x + 1][y]->st != 9 ) {
           
            if (map->Field[x + 1][y]->st == 2) {
                if (rand() % 10 == 0) {
                    map->Field[x + 1][y]->st = 3;
                    map->Field[x + 1][y]->setPixmap(Map().Item1Pix1);

                }
                else if (rand() % 10 == 1) {
                    map->Field[x + 1][y]->st = 4;
                    map->Field[x + 1][y]->setPixmap(Map().Item2Pix1);

                }
                else if (rand() % 10 == 2) {
                    map->Field[x + 1][y]->st = 5;
                    map->Field[x + 1][y]->setPixmap(Map().Item3Pix1);
                }
                else {
                    map->Field[x + 1][y]->st = 9;
                    map->Field[x + 1][y]->setPixmap(Map().FlamePix1);
                }
            }else{
                map->Field[x + 1][y]->st = 9;
                map->Field[x + 1][y]->setPixmap(Map().FlamePix1);
            }
        }
    }
    if (xM1 == true) {
        if (map->Field[x - 1][y]->st != 1 && map->Field[x - 1][y]->st != 9) {
            if (map->Field[x - 1][y]->st == 2) {
                if (rand() % 10 == 0) {
                    map->Field[x - 1][y]->st = 3;
                    map->Field[x - 1][y]->setPixmap(Map().Item1Pix1);

                }
                else if (rand() % 10 == 1) {
                    map->Field[x - 1][y]->st = 4;
                    map->Field[x - 1][y]->setPixmap(Map().Item2Pix1);

                }
                else if (rand() % 10 == 2) {
                    map->Field[x - 1][y]->st = 5;
                    map->Field[x - 1][y]->setPixmap(Map().Item3Pix1);
                }
                else {
                    map->Field[x - 1][y]->st = 9;
                    map->Field[x - 1][y]->setPixmap(Map().FlamePix1);
                }
            }
            else {
                map->Field[x - 1][y]->st = 9;
                map->Field[x - 1][y]->setPixmap(Map().FlamePix1);
            }
        }
    }
    if (yP1 == true) {
        if (map->Field[x][y + 1]->st != 1 && map->Field[x][y + 1]->st != 9 ) {
            if (map->Field[x][y +1]->st == 2) {
                if (rand() % 10 == 0) {
                    map->Field[x][y + 1]->st = 3;
                    map->Field[x][y + 1]->setPixmap(Map().Item1Pix1);

                }
                else if (rand() % 10 == 1) {
                    map->Field[x][y + 1]->st = 4;
                    map->Field[x][y + 1]->setPixmap(Map().Item2Pix1);

                }
                else if (rand() % 10 == 2) {
                    map->Field[x][y + 1]->st = 5;
                    map->Field[x][y + 1]->setPixmap(Map().Item3Pix1);
                }
                else {
                    map->Field[x][y + 1]->st = 9;
                    map->Field[x][y + 1]->setPixmap(Map().FlamePix1);
                }
            }
            else {
                map->Field[x][y + 1]->st = 9;
                map->Field[x][y + 1]->setPixmap(Map().FlamePix1);
            }
        }
    }
    if (yM1 == true) {
        if (map->Field[x][y - 1]->st != 1 && map->Field[x][y - 1]->st != 9 ) {
            if (map->Field[x][y - 1]->st == 2) {
                if (rand() % 10 == 0) {
                    map->Field[x][y - 1]->st = 3;
                    map->Field[x][y - 1]->setPixmap(Map().Item1Pix1);

                }
                else if (rand() % 10 == 1) {
                    map->Field[x][y - 1]->st = 4;
                    map->Field[x][y - 1]->setPixmap(Map().Item2Pix1);

                }
                else if (rand() % 10 == 2) {
                    map->Field[x][y - 1]->st = 5;
                    map->Field[x][y - 1]->setPixmap(Map().Item3Pix1);
                }
                else {
                    map->Field[x][y - 1]->st = 9;
                    map->Field[x][y - 1]->setPixmap(Map().FlamePix1);
                }
            }
            else {
                map->Field[x][y - 1]->st = 9;
                map->Field[x][y - 1]->setPixmap(Map().FlamePix1);
            }
        }
    }
    if (map->Field[x][y]->flame ==true) {
        if (xP2 == true) {
            if (map->Field[x + 2][y]->st != 1 && map->Field[x + 2][y]->st < 9 && map->Field[x + 1][y]->st != 1) {
                if (map->Field[x + 2][y]->st == 2) {
                    if (rand() % 10 == 0) {
                        map->Field[x + 2][y]->st = 3;
                        map->Field[x + 2][y]->setPixmap(Map().Item1Pix1);

                    }
                    else if (rand() % 10 == 1) {
                        map->Field[x + 2][y]->st = 4;
                        map->Field[x + 2][y]->setPixmap(Map().Item2Pix1);

                    }
                    else if (rand() % 10 == 2) {
                        map->Field[x + 2][y]->st = 5;
                        map->Field[x + 2][y]->setPixmap(Map().Item3Pix1);
                    }
                    else {
                        map->Field[x + 2][y]->st = 9;
                        map->Field[x + 2][y]->setPixmap(Map().FlamePix1);
                    }
                }
                else {
                    map->Field[x + 2][y]->st = 9;
                    map->Field[x + 2][y]->setPixmap(Map().FlamePix1);
                }
            }
        }
        if (xM2 == true) {
            if (map->Field[x - 2][y]->st != 1 && map->Field[x - 2][y]->st < 9 && map->Field[x - 1][y]->st != 1 ) {
                if (map->Field[x -2][y]->st == 2) {
                    if (rand() % 10 == 0) {
                        map->Field[x -2][y]->st = 3;
                        map->Field[x -2][y]->setPixmap(Map().Item1Pix1);

                    }
                    else if (rand() % 10 == 1) {
                        map->Field[x -2][y]->st = 4;
                        map->Field[x -2][y]->setPixmap(Map().Item2Pix1);

                    }
                    else if (rand() % 10 == 2) {
                        map->Field[x -2][y]->st = 5;
                        map->Field[x -2][y]->setPixmap(Map().Item3Pix1);
                    }
                    else {
                        map->Field[x -2][y]->st = 9;
                        map->Field[x -2][y]->setPixmap(Map().FlamePix1);
                    }
                }
                else {
                    map->Field[x -2][y]->st = 9;
                    map->Field[x -2][y]->setPixmap(Map().FlamePix1);
                }
            }
        }
        if (yP2 == true) {
            if (map->Field[x][y + 2]->st != 1 && map->Field[x][y + 2]->st < 9 && map->Field[x][y + 1]->st != 1 ) {
                if (map->Field[x][y + 2]->st == 2) {
                    if (rand() % 10 == 0) {
                        map->Field[x][y + 2]->st = 3;
                        map->Field[x][y + 2]->setPixmap(Map().Item1Pix1);

                    }
                    else if (rand() % 10 == 1) {
                        map->Field[x][y + 2]->st = 4;
                        map->Field[x][y + 2]->setPixmap(Map().Item2Pix1);

                    }
                    else if (rand() % 10 == 2) {
                        map->Field[x][y + 2]->st = 5;
                        map->Field[x][y + 2]->setPixmap(Map().Item3Pix1);
                    }
                    else {
                        map->Field[x][y + 2]->st = 9;
                        map->Field[x][y + 2]->setPixmap(Map().FlamePix1);
                    }
                }
                else {
                    map->Field[x][y + 2]->st = 9;
                    map->Field[x][y + 2]->setPixmap(Map().FlamePix1);
                }
            }
        }
        if (yM2 == true) {
            if (map->Field[x][y - 2]->st != 1 && map->Field[x][y - 2]->st < 9 && map->Field[x][y - 1]->st != 1 ) {
                if (map->Field[x][y - 2]->st == 2) {
                    if (rand() % 10 == 0) {
                        map->Field[x][y - 2]->st = 3;
                        map->Field[x][y - 2]->setPixmap(Map().Item1Pix1);

                    }
                    else if (rand() % 10 == 1) {
                        map->Field[x][y - 2]->st = 4;
                        map->Field[x][y - 2]->setPixmap(Map().Item2Pix1);

                    }
                    else if (rand() % 10 == 2) {
                        map->Field[x][y - 2]->st = 5;
                        map->Field[x][y - 2]->setPixmap(Map().Item3Pix1);
                    }
                    else {
                        map->Field[x][y - 2]->st = 9;
                        map->Field[x][y - 2]->setPixmap(Map().FlamePix1);
                    }
                }
                else {
                    map->Field[x][y - 2]->st = 9;
                    map->Field[x][y - 2]->setPixmap(Map().FlamePix1);
                }
            }
        }
    }  
}

void Bomberman::FlameRemove(int x, int y) {

    if (x - 1 >= 0) { xM1 = true; }
    else { xM1 = false; }
    if (x - 2 >= 0) { xM2 = true; }
    else { xM2 = false; }
    if (x + 1 < COLUMN) { xP1 = true; }
    else { xP1 = false; }
    if (x + 2 < COLUMN && map->Field[x+2][y]) { xP2 = true; }
    else { xP2 = false; }

    if (y - 1 >= 0) { yM1 = true; }
    else { yM1 = false; }
    if (y - 2 >= 0) { yM2 = true; }
    else { yM2 = false; }
    if (y + 1 < ROW) { yP1 = true; }
    else { yP1 = false; }
    if (y + 2 < ROW){ yP2 = true; }
    else { yP2 = false; }

    map->Field[x][y]->st = 0;
    map->Field[x][y]->setPixmap(Map().BlockNullPix);

    if (xP1== true) {
        if (map->Field[x + 1][y]->st == 9) {
            map->Field[x + 1][y]->st = 0;
            map->Field[x + 1][y]->setPixmap(Map().BlockNullPix);
        }
    }
    if (xM1 == true) {
        if (map->Field[x - 1][y]->st == 9) {
            map->Field[x - 1][y]->st = 0;
            map->Field[x - 1][y]->setPixmap(Map().BlockNullPix);
        }
    }
        if (yP1 == true) {
            if (map->Field[x][y + 1]->st == 9) {
                map->Field[x][y + 1]->st = 0;
                map->Field[x][y + 1]->setPixmap(Map().BlockNullPix);
            }
        }
    if (yM1 == true) {
        if (map->Field[x][y - 1]->st == 9) {
            map->Field[x][y - 1]->st = 0;
            map->Field[x][y - 1]->setPixmap(Map().BlockNullPix);
        }
    }
    if (map->Field[x][y]->flame == true) {
        if (xP2 == true) {
            if (map->Field[x + 2][y]->st == 9) {
                map->Field[x + 2][y]->st = 0;
                map->Field[x + 2][y]->setPixmap(Map().BlockNullPix);
            }
        }
        if (xM2 == true) {
            if (map->Field[x - 2][y]->st == 9) {
                map->Field[x - 2][y]->st = 0;
                map->Field[x - 2][y]->setPixmap(Map().BlockNullPix);
            }
        }
        if (yP2 == true) {
            if (map->Field[x][y + 2]->st == 9) {
                map->Field[x][y + 2]->st = 0;
                map->Field[x][y + 2]->setPixmap(Map().BlockNullPix);
            }
        }
        if (yM2 == true) {
            if (map->Field[x][y - 2]->st == 9) {
                map->Field[x][y - 2]->st = 0;
                map->Field[x][y - 2]->setPixmap(Map().BlockNullPix);
            }
        }
        map->Field[x][y]->flame = 0;

    }
    map->Field[x][y]->time = 0;

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

        
        //----------Item detection Player1----------------------------//

        QList<QGraphicsItem*> collidingP1 = levelScene->collidingItems(map->player1);

        cBombMerker1 = false;

        for (int i = 0, n = collidingP1.size(); i < n; ++i) {
            if (typeid(*(collidingP1[i])) == typeid(clBlock))
            {
                if (!collidingP1.isEmpty()) {
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 9) {
                        if (scene() == levelScene) {
                            if (pauseMenu->scene() != levelScene) {
                                if (victoryMenu->scene() != levelScene) {
                                    playerWon = 2;
                                    openVictory();
                                }
                            }
                        }
                    }
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 8) {
                        cBombMerker1 = true;
                    }

                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 3) { //Item1
                        flameItem1 = true;
                        map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st = 0;
                        map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->setPixmap(Map().BlockNullPix);
                    }
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 4) { //Item2
                        bombItem1 = true;
                        map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st = 0;
                        map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->setPixmap(Map().BlockNullPix);
                    }
                    if (map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st == 5) { //Item3
                        speedItem1 = true;
                        map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->st = 0;
                        map->Field[int(collidingP1[i]->x() / BLOCK_SIZE)][int(collidingP1[i]->y() / BLOCK_SIZE)]->setPixmap(Map().BlockNullPix);
                    }
                }
            }
            if (typeid(*(collidingP1[i])) == typeid(QGraphicsPixmapItem)) {

                if (map->player1->x() > map->player2->x()) {
                    leftStop1 = true;
                    rightStop2 = true;
                }
                if (map->player1->x() < map->player2->x()) {
                    leftStop2 = true;
                    rightStop1 = true;
                }
                if (map->player1->y() > map->player2->y()) {
                    upStop1 = true;
                    downStop2 = true;
                }
                if (map->player1->y() < map->player2->y()) {
                    upStop2 = true;
                    downStop1 = true;

                }
            }
        }

        // Movment Obstacles avoidens Player1
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE) / BLOCK_SIZE)]->st == 1) { downStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer1 - PLAYER_SPEED) / BLOCK_SIZE)]->st == 1) { upStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 1) { rightStop1 = true; }
        if (map->Field[int((xPlayer1 - PLAYER_SPEED) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 1) { leftStop1 = true; }

        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE) / BLOCK_SIZE)]->st == 2) { downStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer1 - PLAYER_SPEED) / BLOCK_SIZE)]->st == 2) { upStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 2) { rightStop1 = true; }
        if (map->Field[int((xPlayer1 - PLAYER_SPEED) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 2) { leftStop1 = true; }

        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE) / BLOCK_SIZE)]->st == 8 && !bombMerker1) { downStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer1 - PLAYER_SPEED) / BLOCK_SIZE)]->st == 8 && !bombMerker1) { upStop1 = true; }
        if (map->Field[int((xPlayer1 + BLOCK_SIZE) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 8 && !bombMerker1) { rightStop1 = true; }
        if (map->Field[int((xPlayer1 - PLAYER_SPEED) / BLOCK_SIZE)][int((yPlayer1 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 8 && !bombMerker1) { leftStop1 = true; }

        if (cBombMerker1 == false) {
            bombMerker1 = false;
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

        if ((!downStop1 && downKey1 == true && (xPlayer1 % BLOCK_SIZE == 0) || dCorPlayer1) && (map->player1->y() <= MAP_HEIGHT - BLOCK_SIZE - PLAYER_SPEED)) {
            map->player1->moveBy(0, PLAYER_SPEED);
            StatusPlayer1 = 3;
        }
        if ((!leftStop1 && leftKey1 == true && (yPlayer1 % BLOCK_SIZE) == 0 || lCorPlayer1) && map->player1->x() >= PLAYER_SPEED) {
            map->player1->moveBy(-PLAYER_SPEED, 0);
            StatusPlayer1 = 4;

        }
        if ((!rightStop1 && rightKey1 == true && (yPlayer1 % BLOCK_SIZE) == 0 || rCorPlayer1) && (map->player1->x() <= MAP_WIDTH - BLOCK_SIZE - PLAYER_SPEED)) {
            map->player1->moveBy(PLAYER_SPEED, 0);
            StatusPlayer1 = 2;

        }
        if (!upKey1 && !downKey1 && !rightKey1 && !leftKey1) {
            StatusPlayer1 = 0;
        }







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


        //----------Item detection Player2----------------------------//

        QList<QGraphicsItem*> collidingP2 = levelScene->collidingItems(map->player2);

        cBombMerker2 = false;

        for (int i = 0, n = collidingP2.size(); i < n; ++i) {
            if (typeid(*(collidingP2[i])) == typeid(clBlock))
            {
                if (!collidingP2.isEmpty()) {
                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 9) { //Flamme
                        if (scene() == levelScene) {
                            if (pauseMenu->scene() != levelScene) {
                                if (victoryMenu->scene() != levelScene) {
                                    playerWon = 1;
                                    openVictory();
                                }
                            }
                        }
                    }
                    if ((map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 8)) {
                        cBombMerker2 = true;
                    }

                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 3) { //Item1
                        flameItem2 = true;
                        map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st = 0;
                        map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->setPixmap(Map().BlockNullPix);
                    }
                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 4) { //Item2
                        bombItem2 = true;     
                        map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st = 0;
                        map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->setPixmap(Map().BlockNullPix);
                    }
                    if (map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st == 5) { //Item3
                        speedItem2 = true;
                        map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->st = 0;
                        map->Field[int(collidingP2[i]->x() / BLOCK_SIZE)][int(collidingP2[i]->y() / BLOCK_SIZE)]->setPixmap(Map().BlockNullPix);
                    }
                }
            }
        }


        // Movment Obstacles avoidens Player 2
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE) / BLOCK_SIZE)]->st == 1) { downStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer2 - PLAYER_SPEED) / BLOCK_SIZE)]->st == 1) { upStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 1) { rightStop2 = true; }
        if (map->Field[int((xPlayer2 - PLAYER_SPEED) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 1) { leftStop2 = true; }

        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE) / BLOCK_SIZE)]->st == 2) { downStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer2 - PLAYER_SPEED) / BLOCK_SIZE)]->st == 2) { upStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 2) { rightStop2 = true; }
        if (map->Field[int((xPlayer2 - PLAYER_SPEED) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 2) { leftStop2 = true; }


        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE) / BLOCK_SIZE)]->st == 8 && !bombMerker2) { downStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)][int((yPlayer2 - PLAYER_SPEED) / BLOCK_SIZE)]->st == 8 && !bombMerker2) { upStop2 = true; }
        if (map->Field[int((xPlayer2 + BLOCK_SIZE) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 8 && !bombMerker2) { rightStop2 = true; }
        if (map->Field[int((xPlayer2 - PLAYER_SPEED) / BLOCK_SIZE)][int((yPlayer2 + BLOCK_SIZE / 2) / BLOCK_SIZE)]->st == 8 && !bombMerker2) { leftStop2 = true; }

        if(cBombMerker2== false) {
            bombMerker2 = false;
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

        


     }

       
    //refresh Volume
     if (scene() == menuScene)
      {
        soundManager->setVolume(menuScene->getVolume());
      }

    
}



   

