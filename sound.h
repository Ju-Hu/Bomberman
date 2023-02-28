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

    QMediaPlayer* click, *win, *explosion, *music;

    QMediaPlaylist* playlist;

    int newVolume;

public slots:
    void playSound(QString);
    void setVolume(int);

};

#endif