#ifndef MAP_H
#define MAP_H

#include "config.h"


class clBlock : public QObject, public QGraphicsPixmapItem
{
public:
	//--- Konstruktor ---
	clBlock(int _x, int _y, int _w, int _h, int _st) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		st = _st;
	}
	int x;
	int y;
	int w;
	int h;
	int st;
};

void Scale(QPixmap* Pix);



class Map
{
public:

    Map();
  
    ~Map();


    void generateMap1();
  
    void generateMap2();

    void generateMap3();

    //void clearMap();

	clBlock* Field[COLUMN][ROW];

	QGraphicsPixmapItem* player1;
	QGraphicsPixmapItem* player2;

	//Pixmaps for Player1
	QPixmap Player1Pix1st1 = QPixmap("images/player/1.png");
	QPixmap Player1Pix1st2 = QPixmap("images/player/2.png");
	QPixmap Player1Pix1up1 = QPixmap("images/player/3.png");
	QPixmap Player1Pix1up2 = QPixmap("images/player/3.png");
	QPixmap Player1Pix1dw1 = QPixmap("images/player/3.png");
	QPixmap Player1Pix1dw2 = QPixmap("images/player/3.png");
	QPixmap Player1Pix1lf1 = QPixmap("images/player/3.png");
	QPixmap Player1Pix1lf2 = QPixmap("images/player/3.png");
	QPixmap Player1Pix1ri1 = QPixmap("images/player/3.png");
	QPixmap Player1Pix1ri2 = QPixmap("images/player/3.png");
	
	//Pixmaps for Player2
	QPixmap Player2Pix1st1 = QPixmap("images/player/1.png");
	QPixmap Player2Pix1st2 = QPixmap("images/player/2.png");
	QPixmap Player2Pix1up1 = QPixmap("images/player/3.png");
	QPixmap Player2Pix1up2 = QPixmap("images/player/3.png");
	QPixmap Player2Pix1dw1 = QPixmap("images/player/3.png");
	QPixmap Player2Pix1dw2 = QPixmap("images/player/3.png");
	QPixmap Player2Pix1lf1 = QPixmap("images/player/3.png");
	QPixmap Player2Pix1lf2 = QPixmap("images/player/3.png");
	QPixmap Player2Pix1ri1 = QPixmap("images/player/3.png");
	QPixmap Player2Pix1ri2 = QPixmap("images/player/3.png");


	//Pixmaps for Map1
	QPixmap StonePix1 = QPixmap("images/block1.png");
	QPixmap BoxPix1 =	QPixmap("images/block2.png");
	QPixmap BombPix1 =	QPixmap("images/bomb.png");
	QPixmap FlamePix1 = QPixmap("images/flame1.png");
	QPixmap Item1Pix1 = QPixmap("images/powerup1.png");
	QPixmap Item2Pix1 = QPixmap("images/powerup2.png");
	QPixmap Item3Pix1 = QPixmap("images/powerup3.png");


	//Pixmaps for Map2
	QPixmap StonePix2 = QPixmap("images/block1.png");
	QPixmap BoxPix2 =	QPixmap("images/block2.png");
	QPixmap BombPix2 =	QPixmap("images/bomb.png");
	QPixmap FlamePix2 = QPixmap("images/flame1.png");
	QPixmap Item1Pix2 = QPixmap("images/powerup1.png");
	QPixmap Item2Pix2 = QPixmap("images/powerup2.png");
	QPixmap Item3Pix2 = QPixmap("images/powerup3.png");
	QPixmap Player1Pix2 = QPixmap("images/player/3.png");
	QPixmap Player2Pix2 = QPixmap("images/player/3.png");


	//Pixmaps for Map3
	QPixmap StonePix3 = QPixmap("images/block1.png");
	QPixmap BoxPix3 =	QPixmap("images/block2.png");
	QPixmap BombPix3 =	QPixmap("images/bomb.png");
	QPixmap FlamePix3 = QPixmap("images/flame1.png");
	QPixmap Item1Pix3 = QPixmap("images/powerup1.png");
	QPixmap Item2Pix3 = QPixmap("images/powerup2.png");
	QPixmap Item3Pix3 = QPixmap("images/powerup3.png");
	QPixmap Player1Pix3 = QPixmap("images/player/3.png");
	QPixmap Player2Pix3 = QPixmap("images/player/3.png");


	//Pixmaps for Map1
	//QPixmap* StonePix1 ;
	//QPixmap* BoxPix1;
	//QPixmap* BombPix1 ;
	//QPixmap* FlamePix1 ;
	//QPixmap* Item1Pix1 ;
	//QPixmap* Item2Pix1 ;
	//QPixmap* Item3Pix1 ;
	//QPixmap* Player1Pix1 ;
	//QPixmap* Player2Pix1 ;



private:

    int width;

    int height;

    QString mapName;
};

#endif