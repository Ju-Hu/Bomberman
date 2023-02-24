#include "map.h"
using namespace std;

Map::Map()
{
    mapName = "noNamedlevel";
}

Map::~Map()
{
    //clearMap();
}

void Map::generateMap1()
{
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

        for (int c = 0; c < COLUMN; c++) {
            if (modified_input[c] != '\0') {
                field[c][r] = new clBlock(c * BLOCK_SIZE, r * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, modified_input[c] - '0');
                field[c][r]->setPos(field[c][r]->x, field[c][r]->y);
                if (field[c][r]->st == 1) {
                    QPixmap blockimg1 = QPixmap("images/block1.png");
                    blockimg1 = blockimg1.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg1);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 2) {
                    QPixmap blockimg2 = QPixmap("images/block2.png");
                    blockimg2 = blockimg2.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg2);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 3) {
                    QPixmap blockimg3 = QPixmap("images/bomb.png");
                    blockimg3 = blockimg3.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg3);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 4) {
                    QPixmap blockimg4 = QPixmap("images/flame1.png");
                    blockimg4 = blockimg4.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg4);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 5) {
                    QPixmap blockimg5 = QPixmap("images/powerup1.png");
                    blockimg5 = blockimg5.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg5);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 6) {
                    QPixmap blockimg6 = QPixmap("images/powerup2.png");
                    blockimg6 = blockimg6.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg6);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 7) {
                    QPixmap blockimg7 = QPixmap("images/powerup3.png");
                    blockimg7 = blockimg7.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg7);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
            }
        }
        r++;
    }


    //// create the player
    //player = new Player();
    //player->setPos(200, 400);

    mapName = "Map 1";
}

void Map::generateMap2()
{
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

        for (int c = 0; c < COLUMN; c++) {
            if (modified_input[c] != '\0') {
                field[c][r] = new clBlock(c * BLOCK_SIZE, r * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, modified_input[c] - '0');
                field[c][r]->setPos(field[c][r]->x, field[c][r]->y);
                if (field[c][r]->st == 1) {
                    QPixmap blockimg1 = QPixmap("images/block3.png");
                    blockimg1 = blockimg1.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg1);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 2) {
                    QPixmap blockimg2 = QPixmap("images/block4.png");
                    blockimg2 = blockimg2.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg2);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 3) {
                    QPixmap blockimg3 = QPixmap("images/bomb.png");
                    blockimg3 = blockimg3.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg3);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 4) {
                    QPixmap blockimg4 = QPixmap("images/flame1.png");
                    blockimg4 = blockimg4.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg4);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 5) {
                    QPixmap blockimg5 = QPixmap("images/powerup1.png");
                    blockimg5 = blockimg5.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg5);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 6) {
                    QPixmap blockimg6 = QPixmap("images/powerup2.png");
                    blockimg6 = blockimg6.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg6);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
                if (field[c][r]->st == 7) {
                    QPixmap blockimg7 = QPixmap("images/powerup3.png");
                    blockimg7 = blockimg7.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg7);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
            }
        }
        r++;
    }

    mapName = "Map 2";
}

void Map::generateMap3()
{
    width = MAP_WIDTH;
    height = MAP_HEIGHT;

    //// create the player
    //player = new Player();
    //player->setPos(200, 400);

    mapName = "Map 3";
}


//void Map::clearMap()
//{
//    //if (player != NULL) {
//    //    //qDebug() << player;
//    //    delete player;
//    //    player = NULL;
//    //}
//
//    //if (playerInfo != NULL) {
//    //    delete playerInfo;
//    //    playerInfo = NULL;
//    //}
//
//
//    //for (Element* elem : *elementList) {
//    //    delete elem;
//    //}
//    //elementList->clear();
//
// 
//}