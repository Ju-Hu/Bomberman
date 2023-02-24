#include "Bomberman.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("images/icon.png"));

    //Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("images/splash.png"));
    splash->show();

    //Sound
    QMediaPlayer *intro = new QMediaPlayer;
    intro->setMedia(QUrl::fromLocalFile("sounds/Intro.mp3"));
    intro->setVolume(10);
    intro->play();

    Bomberman *game = new Bomberman();
    game ->setMinimumSize(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    QTimer::singleShot(4000, splash, SLOT(close())); //8000
    QTimer::singleShot(4000, intro, SLOT(stop()));
    QTimer::singleShot(4000, game, SLOT(show()));
    QTimer::singleShot(4000, game, SLOT(openMenu()));
    QTimer::singleShot(4000, game, SLOT(showFullScreen())); //showFullScreen()


    return a.exec();
}
