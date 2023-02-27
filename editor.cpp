#include "editor.h"
using namespace std;

Editor::Editor() : QGraphicsScene()
{
    this->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    QImage background = QImage("images/backgrounds/background_menu2.png");
    background = background.scaled(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setBackgroundBrush(background);

    
    /*int xField = 323;
    int yField = 53;*/

    
    int xButton2 = X_FIELD - BTN_GAP - 75;
    int xButton = xButton2 - BTN_GAP - 75;
    int yStartButton = Y_FIELD;
    
    int index1 = 0;
    int index2 = 0;

    // LoadLVL1 Btn
    LoadLvl1Btn = new EditorButton(0, 0, "Load 1");
    LoadLvl1Btn->resize(75, 75);
    LoadLvl1Btn->setStyleSheet("border-image:url(images/editorneutral.png);");
    LoadLvl1Btn->move(xButton, yStartButton + index1 * (LoadLvl1Btn->height() + BTN_GAP));
    LoadLvl1Btn->setText(LoadLvl1Btn->text);
    QFont font;
    font.setBold(true);
    font.setPixelSize(20);
    setFont(font);
    this->addWidget(LoadLvl1Btn);
    index1++;

    // LoadLVL2 Btn
    LoadLvl2Btn = new EditorButton(0, 0, "Load 2");
    LoadLvl2Btn->resize(75, 75);
    LoadLvl2Btn->setStyleSheet("border-image:url(images/editorneutral.png);");
    LoadLvl2Btn->move(xButton, yStartButton + index1 * (LoadLvl2Btn->height() + BTN_GAP));
    LoadLvl2Btn->setText(LoadLvl2Btn->text);
    this->addWidget(LoadLvl2Btn);
    index1++;

    // LoadLVL3 Btn
    LoadLvl3Btn = new EditorButton(0, 0, "Load 3");
    LoadLvl3Btn->resize(75, 75);
    LoadLvl3Btn->setStyleSheet("border-image:url(images/editorneutral.png);");
    LoadLvl3Btn->move(xButton, yStartButton + index1 * (LoadLvl3Btn->height() + BTN_GAP));
    LoadLvl3Btn->setText(LoadLvl3Btn->text);
    this->addWidget(LoadLvl3Btn);
    index1++;

    // LoadLVL4 Btn
    LoadLvl4Btn = new EditorButton(0, 0, "Clear");
    LoadLvl4Btn->resize(75, 75);
    LoadLvl4Btn->setStyleSheet("border-image:url(images/editorneutral.png);");
    LoadLvl4Btn->move(xButton, yStartButton + index1 * (LoadLvl4Btn->height() + BTN_GAP));
    LoadLvl4Btn->setText(LoadLvl4Btn->text);
    this->addWidget(LoadLvl4Btn);

    // LVL1 Btn
    Lvl1Btn = new EditorButton(0, 0, "Save 1");
    Lvl1Btn->resize(75, 75);
    Lvl1Btn->setStyleSheet("border-image:url(images/editorsave.png);");
    Lvl1Btn->move(xButton2, yStartButton + index2 * (Lvl1Btn->height() + BTN_GAP));
    Lvl1Btn->setText(Lvl1Btn->text);
    this->addWidget(Lvl1Btn);
    index2++;

    // LVL2 Btn
    Lvl2Btn = new EditorButton(0, 0, "Save 2");
    Lvl2Btn->resize(75, 75);
    Lvl2Btn->setStyleSheet("border-image:url(images/editorsave.png);");
    Lvl2Btn->move(xButton2, yStartButton + index2 * (Lvl2Btn->height() + BTN_GAP));
    Lvl2Btn->setText(Lvl2Btn->text);
    this->addWidget(Lvl2Btn);
    index2++;

    // LVL3 Btn
    Lvl3Btn = new EditorButton(0, 0, "Save 3");
    Lvl3Btn->resize(75, 75);
    Lvl3Btn->setStyleSheet("border-image:url(images/editorsave.png);");
    Lvl3Btn->move(xButton2, yStartButton + index2 * (Lvl3Btn->height() + BTN_GAP));
    Lvl3Btn->setText(Lvl3Btn->text);
    this->addWidget(Lvl3Btn);
    index2++;

    // display menuBtn
    MenuBtn = new EditorButton(0, 0, "Menu");
    MenuBtn->resize(75, 75);
    MenuBtn->setStyleSheet("border-image:url(images/editorexit.png);");
    MenuBtn->move(xButton2, yStartButton + index2 * (MenuBtn->height() + BTN_GAP));
    MenuBtn->setText(MenuBtn->text);
    this->addWidget(MenuBtn);

    // generate Map Editor
    ifstream source("maps/editor.txt"); //"map1.txt"
    string input;
    string modified_input;
    regex reg("[^0-7]");
    int btnindex = 0;
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
                if (modified_input[c] - '0' == 0) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "0");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/block0.png);");
                    this->addWidget(editField[c][r]);
                }
                if (modified_input[c] - '0' == 1) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "1");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/block3.png);");
                    this->addWidget(editField[c][r]);
                }
                if (modified_input[c] - '0' == 2) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "2");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/block4.png);");
                    this->addWidget(editField[c][r]);
                }
                if (modified_input[c] - '0' == 3) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "3");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/powerup1.png);");
                    this->addWidget(editField[c][r]);
                }
                if (modified_input[c] - '0' == 4) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "4");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/powerup2.png);");
                    this->addWidget(editField[c][r]);
                }
                if (modified_input[c] - '0' == 5) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "5");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/powerup3.png);");
                    this->addWidget(editField[c][r]);
                }
                if (modified_input[c] - '0' == 6) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "6");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/player/player1/stop1.png);");
                    this->addWidget(editField[c][r]);
                }
                if (modified_input[c] - '0' == 7) {
                    editField[c][r] = new EditorButton(btnindex, modified_input[c] - '0', "7");
                    editField[c][r]->resize(75, 75);
                    editField[c][r]->move((c * BLOCK_SIZE) + X_FIELD, r * BLOCK_SIZE + Y_FIELD);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/player/player2/stop1.png);");
                    this->addWidget(editField[c][r]);
                }
                btnindex++;
            }
        }
        r++;
    }
}

Editor::~Editor()
{
    delete Lvl1Btn;
    delete Lvl2Btn;
    delete Lvl3Btn;
    delete MenuBtn;
}

EditorButton* Editor::loadLvl1Btn() const
{
    return LoadLvl1Btn;
}
EditorButton* Editor::loadLvl2Btn() const
{
    return LoadLvl2Btn;
}
EditorButton* Editor::loadLvl3Btn() const
{
    return LoadLvl3Btn;
}
EditorButton* Editor::loadLvl4Btn() const
{
    return LoadLvl4Btn;
}
EditorButton* Editor::setLvl1Btn() const
{
    return Lvl1Btn;
}
EditorButton* Editor::setLvl2Btn() const
{
    return Lvl2Btn;
}
EditorButton* Editor::setLvl3Btn() const
{
    return Lvl3Btn;
}

EditorButton* Editor::getMenuBtn() const
{
    return MenuBtn;
}

void Editor::loadEditor(int loadTXT)
{
    ifstream inStream; //"map1.txt"
    if (loadTXT == 1) { inStream.open("maps/map1.txt"); }
    if (loadTXT == 2) { inStream.open("maps/map2.txt"); }
    if (loadTXT == 3) { inStream.open("maps/map3.txt"); }
    if (loadTXT == 4) { inStream.open("maps/editor.txt"); }

    string inputString;
    string modified_inputString;
    regex reg("[^0-7]");
    int btnindex = 0;
    for (int r = 0; r < ROW;) {
        inputString.clear();
        getline(inStream, inputString);
        modified_inputString = regex_replace(inputString, reg, "");
        if (!modified_inputString.empty())
        {
            modified_inputString.resize(COLUMN, '0');
        }
        if ((r < ROW) && (modified_inputString.empty()))
        {
            modified_inputString = "00000000000000000";
        }
        for (int c = 0; c < COLUMN; c++) {
            if (modified_inputString[c] != '\0') {
                if (modified_inputString[c] - '0' == 0) {
                    editField[c][r]->st = 0;
                    editField[c][r]->text = QString::number(0);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/block0.png);");
                }
                if (modified_inputString[c] - '0' == 1) {
                    editField[c][r]->st = 1;
                    editField[c][r]->text = QString::number(1);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/block3.png);");
                }
                if (modified_inputString[c] - '0' == 2) {
                    editField[c][r]->st = 2;
                    editField[c][r]->text = QString::number(2);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/block4.png);");
                }
                if (modified_inputString[c] - '0' == 3) {
                    editField[c][r]->st = 3;
                    editField[c][r]->text = QString::number(3);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/powerup1.png);");
                }
                if (modified_inputString[c] - '0' == 4) {
                    editField[c][r]->st = 4;
                    editField[c][r]->text = QString::number(4);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/powerup2.png);");
                }
                if (modified_inputString[c] - '0' == 5) {
                    editField[c][r]->st = 5;
                    editField[c][r]->text = QString::number(5);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/powerup3.png);");
                }
                if (modified_inputString[c] - '0' == 6) {
                    editField[c][r]->st = 6;
                    editField[c][r]->text = QString::number(6);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/player/player1/stop1.png);");
                }
                if (modified_inputString[c] - '0' == 7) {
                    editField[c][r]->st = 7;
                    editField[c][r]->text = QString::number(7);
                    //editField[c][r]->setText(editField[c][r]->text);
                    editField[c][r]->setStyleSheet("border-image:url(images/player/player2/stop1.png);");
                }
                btnindex++;
            }
        }
        r++;
    }
}

void Editor::saveEditor(int saveTXT)
{
    ofstream outStream;
    if (saveTXT == 1) { outStream.open("maps/map1.txt", std::ofstream::out | std::ofstream::trunc); };
    if (saveTXT == 2) { outStream.open("maps/map2.txt", std::ofstream::out | std::ofstream::trunc); };
    if (saveTXT == 3) { outStream.open("maps/map3.txt", std::ofstream::out | std::ofstream::trunc); };
    string outputString;
    int btnindex = 0;
    for (int r = 0; r < ROW;) {
        outputString.clear();
        for (int c = 0; c < COLUMN; c++) {
            if (editField[c][r]->st == 0) {
                outputString += "0";
            }
            if (editField[c][r]->st == 1) {
                outputString += "1";
            }
            if (editField[c][r]->st == 2) {
                outputString += "2";
            }
            if (editField[c][r]->st == 3) {
                outputString += "3";
            }
            if (editField[c][r]->st == 4) {
                outputString += "4";
            }
            if (editField[c][r]->st == 5) {
                outputString += "5";
            }
            if (editField[c][r]->st == 6) {
                outputString += "6";
            }
            if (editField[c][r]->st == 7) {
                outputString += "7";
            }
            btnindex++;
        }
        outputString += "\n";
        outStream << outputString;
        r++;
    }
    outStream.close();
}