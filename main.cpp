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
    intro->setVolume(30);
    intro->play();

    Bomberman *game = new Bomberman();
    game ->setMinimumSize(1366, 768); // Steam Umfrage: >97% benutzen diese odr höhere Auflösung
   
    QTimer::singleShot(1000, splash, SLOT(close()));
    QTimer::singleShot(1000, game, SLOT(show()));
    QTimer::singleShot(1000, game, SLOT(openMenu()));
    QTimer::singleShot(1000, game, SLOT(showFullScreen())); //showFullScreen()

    return a.exec();
}
