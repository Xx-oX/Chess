#include "mainwindow.h"
#include "dialog.h"
#include "promotion.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>

extern int isEditor = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    start StartWindow;
    //Dialog Editor(1);
    promotion p;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/audio/Audio/backGround.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *musik = new QMediaPlayer();
    musik->setPlaylist(playlist);
    musik->play();


    //p.show();
    //return a.exec();

    if(StartWindow.exec() == QDialog::Accepted){
        isEditor = 1;
        qDebug()<<"g";
        MainWindow w;
        w.show();
        return a.exec();
    }else {
        musik->stop();
        return 0;
    }
}
