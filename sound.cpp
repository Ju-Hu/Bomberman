#include "sound.h"

Sound::Sound(QWidget* parent) : QDialog(parent){

    this->click = new QMediaPlayer;
    click->setMedia(QUrl("sounds/click.wav"));
    click->setVolume(40);

    this->win = new QMediaPlayer;
    win->setMedia(QUrl("sounds/win.mp3"));
    win->setVolume(20);

    this->explosion = new QMediaPlayer;
    explosion->setMedia(QUrl("sounds/explosion.mp3"));
    explosion->setVolume(20);

    this->playlist = new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    playlist->addMedia(QUrl("sounds/menu.mp3"));
    playlist->addMedia(QUrl("sounds/map1.mp3"));
    playlist->addMedia(QUrl("sounds/map2.mp3"));
    playlist->addMedia(QUrl("sounds/map3.mp3"));
    playlist->setCurrentIndex(0);

    this->music = new QMediaPlayer;
    music->setPlaylist(playlist);
}

Sound::~Sound() {
}

void Sound::setVolume(int volume)
{
    music->setVolume(MUSIC_VOLUME * volume);
    click->setVolume(EFFECT_VOLUME * volume);
    win->setVolume(EFFECT_VOLUME * volume * 3);
    explosion->setVolume(EFFECT_VOLUME * volume);
    newVolume = MUSIC_VOLUME * volume;
}

void Sound::playSound(QString which) {


    if (which == "click") {
        if (click->PlayingState == 1)
            click->stop();
        click->play();
    }
    else if (which == "explosion") {
        if(explosion->PlayingState == 1)
            explosion->stop();
        explosion->play();
    }
    else if (which == "win") {

        win->play();
    }
    else if (which == "menu") {

        playlist->setCurrentIndex(0);
        music->play();
    }
    else if (which == "map1") {

        playlist->setCurrentIndex(1);
    }
    else if (which == "map2") {

        playlist->setCurrentIndex(2);
    }
    else if (which == "map3") {

        playlist->setCurrentIndex(3);
    }
    else if (which == "stopMusic") {

        music->stop();
    }
    else if (which == "startPauseMusic") {

        music->setVolume(newVolume/4);
    }
    else if (which == "stopPauseMusic") {
 
        music->setVolume(newVolume);
    }

    else {
        return;
    }
}