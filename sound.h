#ifndef SOUND_H
#define SOUND_H


#include <QDialog>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaResource>
#include <QSoundEffect>

class Sound : public QDialog
{
    Q_OBJECT

public:
    explicit Sound(QWidget* parent = 0);
    ~Sound();

private:

    QSoundEffect * run, * bomb, * explosion, * pickup, * pause, * win;

    QMediaPlayer* click, * menu, * map1, * map2, * map3;

public slots:
    void playSound(QString);

};

#endif