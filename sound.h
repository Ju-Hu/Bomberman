#ifndef SOUND_H
#define SOUND_H

#include "config.h"

class Sound : public QDialog
{
    Q_OBJECT

public:
    explicit Sound(QWidget* parent = 0);
    ~Sound();

private:

    QSoundEffect * run, * bomb, * explosion, * pickup, * pause, * win;

    QMediaPlayer* click, * menu, * map1, * map2, * map3;

    int newVolume;

public slots:
    void playSound(QString);
    void setVolume(int);

};

#endif