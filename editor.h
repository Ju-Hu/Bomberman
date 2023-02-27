#ifndef EDITOR_H
#define EDITOR_H

#include "config.h"

class EditorButton : public QPushButton
{
    //Q_OBJECT

public:

    EditorButton(int _btnID, int _st, QString _text)
    {
        btnID = _btnID;
        st = _st;
        text = _text;
    }
    int btnID; //index
    int st; //status
    QString text;
};


class Editor : public QGraphicsScene
{
public:

    Editor();

    ~Editor();

    EditorButton* loadLvl1Btn() const;

    EditorButton* loadLvl2Btn() const;

    EditorButton* loadLvl3Btn() const;

    EditorButton* loadLvl4Btn() const;

    EditorButton* setLvl1Btn() const;

    EditorButton* setLvl2Btn() const;

    EditorButton* setLvl3Btn() const;

    EditorButton* getMenuBtn() const;

    EditorButton* editField[COLUMN][ROW];

    void loadEditor(int loadTXT);

    void saveEditor(int saveTXT);

private:

    EditorButton* LoadLvl1Btn;

    EditorButton* LoadLvl2Btn;

    EditorButton* LoadLvl3Btn;

    EditorButton* LoadLvl4Btn;

    EditorButton* Lvl1Btn;

    EditorButton* Lvl2Btn;

    EditorButton* Lvl3Btn;

    EditorButton* MenuBtn;

};

#endif