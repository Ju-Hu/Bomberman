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
    regex reg("[^0-3]");
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
                    QPixmap blockimg = QPixmap("images/block.png");
                    blockimg = blockimg.scaled(BLOCK_SIZE, BLOCK_SIZE);
                    field[c][r]->setPixmap(blockimg);
                    field[c][r]->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
                }
            }
        }
        r++;
    }


    //// create the player
    //player = new Player();
    //player->setPos(200, 400);

    //Player erzeugen
    player1 = new QGraphicsPixmapItem;
    player1->setPos(COLUMN*BLOCK_SIZE-BLOCK_SIZE, ROW * BLOCK_SIZE - BLOCK_SIZE);
    QPixmap playerImg1 = QPixmap("images/block1.png");
    playerImg1 = playerImg1.scaled(BLOCK_SIZE, BLOCK_SIZE);
    player1->setPixmap(playerImg1);
    player1->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape
    
    player2 = new QGraphicsPixmapItem;
    player2->setPos(BLOCK_SIZE, BLOCK_SIZE);
    QPixmap playerImg2 = QPixmap("images/block1.png");
    playerImg2 = playerImg2.scaled(BLOCK_SIZE, BLOCK_SIZE);
    player2->setPixmap(playerImg2);
    player2->setShapeMode(QGraphicsPixmapItem::BoundingRectShape); //MaskShape

    mapName = "Map 1";
}

void Map::generateMap2()
{
    width = MAP_WIDTH;
    height = MAP_HEIGHT;

    //// create the player
    //player = new Player();
    //player->setPos(200, 400);

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