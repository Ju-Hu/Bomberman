#ifndef CONFIG_H
#define CONFIG_H

#include <QtWidgets/QMainWindow>
#include <qsplashscreen.h>      //Screen beim Boot
#include <QTimer>
#include <QGraphicsView>
#include <Qlist>
#include <qscrollbar.h>
#include <QGraphicsItemGroup>
#include <QSignalMapper>
#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QLabel>
#include <QKeyEvent>
#include <QPainter>   
#include <fstream>
#include <string>
#include <regex>
#include <iostream>


#include <QMediaPlayer>         //Musik
#include <QMediaPlaylist>
#include <QSoundEffect>         //Soundeffekt

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define MAX_SPEED 10

#define PLAYER_WIDTH 39
#define PLAYER_HEIGHT 60

#define MAP_HEIGHT 975
#define MAP_WIDTH 1275

#define COLUMN 17			//Spalte
#define ROW 13				//Reihe

#define PLAYER_SIZE 75
#define PLAYER_SPEED 1

#define BOMB_SIZE 20
#define BOMB_TIMER 5

#define BLOCK_SIZE 75

#define BTN_GAP 50

#define FPS 60

#define TITLE "Bomberman V1"

#endif