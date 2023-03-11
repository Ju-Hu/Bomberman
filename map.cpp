#include "map.h"

using namespace std;

Map::Map()
{
    mapName = "noNamedlevel";


    Scale(&Player1Pix1st1);
    Scale(&Player1Pix1st2);
    Scale(&Player1Pix1st3);
    Scale(&Player1Pix1st4);
    Scale(&Player1Pix1up1);
    Scale(&Player1Pix1up2);
    Scale(&Player1Pix1dw1);
    Scale(&Player1Pix1dw2);
    Scale(&Player1Pix1lf1);
    Scale(&Player1Pix1lf2);
    Scale(&Player1Pix1ri1);
    Scale(&Player1Pix1ri2);
    Scale(&Player1Pix1dead);

    Scale(&Player2Pix1st1);
    Scale(&Player2Pix1st2);
    Scale(&Player2Pix1st3);
    Scale(&Player2Pix1st4);
    Scale(&Player2Pix1up1);
    Scale(&Player2Pix1up2);
    Scale(&Player2Pix1dw1);
    Scale(&Player2Pix1dw2);
    Scale(&Player2Pix1lf1);
    Scale(&Player2Pix1lf2);
    Scale(&Player2Pix1ri1);
    Scale(&Player2Pix1ri2);
    Scale(&Player2Pix1dead);

    Scale(&BlockNullPix);

    Scale(&BombPix1);
    Scale(&FlamePix1);
    Scale(&FlamePix2);
    Scale(&FlamePix3);
    Scale(&Item1Pix1);
    Scale(&Item2Pix1);
    Scale(&Item3Pix1);

    Scale(&StonePix1);
    Scale(&BoxPix1);

    Scale(&StonePix2);
    Scale(&BoxPix2);

    Scale(&StonePix3);
    Scale(&BoxPix3);
}

Map::~Map()
{
    //clearMap();
}

void Scale(QPixmap* Pix) {
    *Pix= Pix->scaled(BLOCK_SIZE, BLOCK_SIZE);
}

void Map::generateMap1()
{
    Playercount1 = new int(0);
    Playercount2 = new int(0);

    /*------------------Reading Map from TXT-------------------------*/
    ifstream source("maps/map1.txt"); //"map1.txt"
    string input;
    string modified_input;
    regex reg("[^0-7]");
    for (int r = 0; r < ROW;) {
        input.clear();
        getline(source, input);
        modified_input = regex_replace(input, reg, "");
        if (!modified_input.empty())
        {
            modified_input.resize(COLUMN, '0');
        }
        if ((r < ROW) && (modified_input.empty()))
        {
            modified_input = "00000000000000000";
        }

    /*--------------------Creating Map-------------------------------*/
        for (int c = 0; c < COLUMN; c++) {
            if (modified_input[c] != '\0') {
                Field[c][r] = new clBlock(c * BLOCK_SIZE, r * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, modified_input[c] - '0',0, false);
                Field[c][r]->setPos(Field[c][r]->x, Field[c][r]->y);
                Field[c][r]->setShapeMode(QGraphicsPixmapItem::MaskShape);
                
                //Create Stone
                if (Field[c][r]->st == 1) {
                    Field[c][r]->setPixmap(StonePix1);
                }
                //Create Box
                if (Field[c][r]->st == 2) {
                    Field[c][r]->setPixmap(BoxPix1);
                }
                //Create Item1
                if (Field[c][r]->st == 3) {
                    Field[c][r]->setPixmap(Item1Pix1);
                }
                //Create Item2
                if (Field[c][r]->st == 4) {
                    Field[c][r]->setPixmap(Item2Pix1);
                }
                //Create Item3
                if (Field[c][r]->st == 5) {
                    Field[c][r]->setPixmap(Item3Pix1);
                }
                //Create Player1
                if (Field[c][r]->st == 6) {
                    player1 = new QGraphicsPixmapItem;
                    player1->setPos(Field[c][r]->x, Field[c][r]->y);
                    player1->setPixmap(Player1Pix1st1);
                    Playercount1++;
                }
                //Create Player2
                if (Field[c][r]->st == 7) {
                    player2 = new QGraphicsPixmapItem;
                    player2->setPos(Field[c][r]->x, Field[c][r]->y);
                    player2->setPixmap(Player2Pix1st1);
                    Playercount2++;
                }
 
            }
        }
        r++;
    }

    //----- default Player
    if (*Playercount1 == 0) {
        player1 = new QGraphicsPixmapItem;
        player1->setPos(Field[COLUMN-2][ROW -2]->x, Field[COLUMN - 2][ROW - 2]->y);
        player1->setPixmap(Player1Pix1st1);
        player1->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    }
    if (*Playercount2 == 0) {
        player2 = new QGraphicsPixmapItem;
        player2->setPos(Field[1][1]->x, Field[1][1]->y);
        player2->setPixmap(Player2Pix1st1);
        player2->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    }
    mapName = "Map 1";
}

void Map::generateMap2()
{
    Playercount1 = new int(0);
    Playercount2 = new int(0);


    /*------------------Reading Map from TXT-------------------------*/
    ifstream source("maps/map2.txt"); //"map1.txt"
    string input;
    string modified_input;
    regex reg("[^0-7]");
    for (int r = 0; r < ROW;) {
        input.clear();
        getline(source, input);
        modified_input = regex_replace(input, reg, "");
        if (!modified_input.empty())
        {
            modified_input.resize(COLUMN, '0');
        }
        if ((r < ROW) && (modified_input.empty()))
        {
            modified_input = "00000000000000000";
        }

        /*--------------------Creating Map-------------------------------*/
        for (int c = 0; c < COLUMN; c++) {
            if (modified_input[c] != '\0') {
                Field[c][r] = new clBlock(c * BLOCK_SIZE, r * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, modified_input[c] - '0', 0, false);
                Field[c][r]->setPos(Field[c][r]->x, Field[c][r]->y);
                Field[c][r]->setShapeMode(QGraphicsPixmapItem::MaskShape);


                //Create Stone
                if (Field[c][r]->st == 1) {
                    Field[c][r]->setPixmap(StonePix2);
                }
                //Create Box
                if (Field[c][r]->st == 2) {
                    Field[c][r]->setPixmap(BoxPix2);
                }
                //Create Item1
                if (Field[c][r]->st == 3) {
                    Field[c][r]->setPixmap(Item1Pix1);
                }
                //Create Item2
                if (Field[c][r]->st == 4) {
                    Field[c][r]->setPixmap(Item2Pix1);
                }
                //Create Item3
                if (Field[c][r]->st == 5) {
                    Field[c][r]->setPixmap(Item3Pix1);
                }
                //Create Player1
                if (Field[c][r]->st == 6) {
                    player1 = new QGraphicsPixmapItem;
                    player1->setPos(Field[c][r]->x, Field[c][r]->y);
                    player1->setPixmap(Player1Pix1st1);
                    Playercount1++;
                }
                //Create Player2
                if (Field[c][r]->st == 7) {
                    player2 = new QGraphicsPixmapItem;
                    player2->setPos(Field[c][r]->x, Field[c][r]->y);
                    player2->setPixmap(Player2Pix1st1);
                    Playercount2++;

                }

            }
        }
        r++;
    }

    //----- default Player
    if (*Playercount1 == 0) {
        player1 = new QGraphicsPixmapItem;
        player1->setPos(Field[COLUMN - 2][ROW - 2]->x, Field[COLUMN - 2][ROW - 2]->y);
        player1->setPixmap(Player1Pix1st1);
        player1->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    }
    if (*Playercount2 == 0) {
        player2 = new QGraphicsPixmapItem;
        player2->setPos(Field[1][1]->x, Field[1][1]->y);
        player2->setPixmap(Player2Pix1st1);
        player2->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    }
    mapName = "Map 2";
}

void Map::generateMap3()
{
    Playercount1 = new int(0);
    Playercount2 = new int(0);


    /*------------------Reading Map from TXT-------------------------*/
    ifstream source("maps/map3.txt"); //"map1.txt"
    string input;
    string modified_input;
    regex reg("[^0-7]");
    for (int r = 0; r < ROW;) {
        input.clear();
        getline(source, input);
        modified_input = regex_replace(input, reg, "");
        if (!modified_input.empty())
        {
            modified_input.resize(COLUMN, '0');
        }
        if ((r < ROW) && (modified_input.empty()))
        {
            modified_input = "00000000000000000";
        }

        /*--------------------Creating Map-------------------------------*/
        for (int c = 0; c < COLUMN; c++) {
            if (modified_input[c] != '\0') {
                Field[c][r] = new clBlock(c * BLOCK_SIZE, r * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, modified_input[c] - '0', 0, false);
                Field[c][r]->setPos(Field[c][r]->x, Field[c][r]->y);
                Field[c][r]->setShapeMode(QGraphicsPixmapItem::MaskShape);


                //Create Stone
                if (Field[c][r]->st == 1) {
                    Field[c][r]->setPixmap(StonePix3);
                }
                //Create Box
                if (Field[c][r]->st == 2) {
                    Field[c][r]->setPixmap(BoxPix3);
                }
                //Create Item1
                if (Field[c][r]->st == 3) {
                    Field[c][r]->setPixmap(Item1Pix1);
                }
                //Create Item2
                if (Field[c][r]->st == 4) {
                    Field[c][r]->setPixmap(Item2Pix1);
                }
                //Create Item3
                if (Field[c][r]->st == 5) {
                    Field[c][r]->setPixmap(Item3Pix1);
                }
                //Create Player1
                if (Field[c][r]->st == 6) {
                    player1 = new QGraphicsPixmapItem;
                    player1->setPos(Field[c][r]->x, Field[c][r]->y);
                    player1->setPixmap(Player1Pix1st1);
                    Playercount1++;
                }
                //Create Player2
                if (Field[c][r]->st == 7) {
                    player2 = new QGraphicsPixmapItem;
                    player2->setPos(Field[c][r]->x, Field[c][r]->y);
                    player2->setPixmap(Player2Pix1st1);
                    Playercount2++;
                }

            }
        }
        r++;
    }


    //----- default Player
    if (*Playercount1 == 0) {
        player1 = new QGraphicsPixmapItem;
        player1->setPos(Field[COLUMN - 2][ROW - 2]->x, Field[COLUMN - 2][ROW - 2]->y);
        player1->setPixmap(Player1Pix1st1);
        player1->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    }
    if (*Playercount2 == 0) {
        player2 = new QGraphicsPixmapItem;
        player2->setPos(Field[1][1]->x, Field[1][1]->y);
        player2->setPixmap(Player2Pix1st1);
        player2->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    }
    mapName = "Map 3";
}

