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

class Map
{
public:

    Map();
  
    ~Map();

 
    void generateMap1();
  
    void generateMap2();

    void generateMap3();

    //void clearMap();

	clBlock* field[COLUMN][ROW];

private:

    int width;

    int height;

    QString mapName;
};

#endif