#include "sound.h"

Sound::Sound(QWidget* parent) : QDialog(parent){

    this->click = new QMediaPlayer;
    click->setMedia(QUrl("sounds/click.wav"));
    click->setVolume(40);

    /*this->run = new QSoundEffect;
    run->setSource(QUrl("sounds/click.wav"));
    run->setLoopCount(0);
    run->setVolume(.25f);

    this->bomb = new QSoundEffect;
    bomb->setSource(QUrl("sounds/click.wav"));
    bomb->setLoopCount(0);
    bomb->setVolume(.25f);

    this->explosion = new QSoundEffect;
    explosion->setSource(QUrl("sounds/click.wav"));
    explosion->setLoopCount(0);
    explosion->setVolume(.25f);

    this->pickup = new QSoundEffect;
    pickup->setSource(QUrl("sounds/click.wav"));
    pickup->setLoopCount(0);
    pickup->setVolume(.25f);

    this->pause = new QSoundEffect;
    pause->setSource(QUrl("sounds/click.wav"));
    pause->setLoopCount(0);
    pause->setVolume(.25f);

    this->win = new QSoundEffect;
    win->setSource(QUrl("sounds/click.wav"));
    win->setLoopCount(0);
    win->setVolume(.25f);*/

    this->menu = new QMediaPlayer;
    menu->setMedia(QUrl("sounds/menu.mp3"));
    menu->setVolume(20);

    this->map1 = new QMediaPlayer;
    map1->setMedia(QUrl("sounds/map1.mp3"));
    map1->setVolume(20);

    this->map2 = new QMediaPlayer;
    map2->setMedia(QUrl("sounds/map2.mp3"));
    map2->setVolume(20);

    this->map3 = new QMediaPlayer;
    map3->setMedia(QUrl("sounds/map3.mp3"));
    map3->setVolume(20);
}

Sound::~Sound() {
}

void Sound::setVolume(int volume)
{
    //qDebug() << "setVolume " << volume;
    menu->setVolume(MUSIC_VOLUME * volume);
    map1->setVolume(MUSIC_VOLUME * volume);
    map2->setVolume(MUSIC_VOLUME * volume);
    map3->setVolume(MUSIC_VOLUME * volume);
    click->setVolume(EFFECT_VOLUME * volume);
    newVolume = MUSIC_VOLUME * volume;
}

void Sound::playSound(QString which) {


    if (which == "click") {

        click->play();
        QTimer::singleShot(250, click, SLOT(stop()));
    }
    else if (which == "run") {

        run->play();
    }
    else if (which == "bomb") {

        bomb->play();
    }
    else if (which == "explosion") {

        explosion->play();
    }
    else if (which == "pickup") {

        pickup->play();
    }
    else if (which == "pause") {

        pause->play();
    }
    else if (which == "win") {

        win->play();
    }
    else if (which == "menu") {

        menu->play();
    }
    else if (which == "map1") {

        map1->play();
    }
    else if (which == "map2") {

        map2->play();
    }
    else if (which == "map3") {

        map3->play();
    }
    else if (which == "stopMusic") {

        menu->stop();
        map1->stop();
        map2->stop();
        map3->stop();
    }
    else if (which == "startPauseMusic") {
        
        menu->setVolume(newVolume/4);
        map1->setVolume(newVolume/4);
        map2->setVolume(newVolume/4);
        map3->setVolume(newVolume/4);
    }
    else if (which == "stopPauseMusic") {
        
        menu->setVolume(newVolume);
        map1->setVolume(newVolume);
        map2->setVolume(newVolume);
        map3->setVolume(newVolume);
    }

    else {
        return;
    }
}