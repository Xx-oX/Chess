#include "mainwindow.h"
#include "ui_mainwindow.h"
int themeNum = 2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Chess by 0_o"));
    this->gameScene = new MyScene(
    0, 0,
    ui->gameGraphicsView->width()-2,
    ui->gameGraphicsView->height()-2
    );

    Timer = new QTimer(this);
    Timer->start(1000);
    connect(Timer,SIGNAL(timeout()),this,SLOT(playChangeSide()));

    pause = new theme;
    pause->hide();
    connect(pause,SIGNAL(send(int)),this,SLOT(recieve(int)));

    ui->gameGraphicsView->setScene(gameScene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Pause_clicked()
{
    pause->exec();
}

void MainWindow::recieve(int a)
{
    themeNum = a;
    qDebug()<<"theme"<<a;
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            gameScene->grid[i][j]->setImg();
        }
    }
    switch(themeNum){
    case 1:
        gameScene->board->setPixmap(QPixmap(":/gridImg/Image/bg_Clasic.png"));
        break;
    case 2:
        gameScene->board->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/bg_Newpaper.png"));
        break;
    case 3:
        gameScene->board->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/bg_8bit.png"));
        break;
    }
}
