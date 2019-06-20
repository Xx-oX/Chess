#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(int mode,QWidget *parent,bool a,QString ip) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->Scene = new editorScene(
                0, 0,
                ui->editorGraphicsView->width()-2,
                ui->editorGraphicsView->height()-2
                );
    qDebug()<<a;
    this->NetScene = new Multi(
                ip,
                a,
                0, 0,
                ui->editorGraphicsView->width()-2,
                ui->editorGraphicsView->height()-2
                );
    if(mode == 1){
        setWindowTitle(tr("Editor"));
        ui->editorGraphicsView->setScene(Scene);
    }
    else if(mode == 2){
        setWindowTitle(tr("NetGame"));
        ui->editorGraphicsView->setScene(NetScene);
    }


    pause = new theme;
    pause->hide();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pause_clicked()
{
    pause->exec();
}

void Dialog::on_back_clicked()
{
    this->hide();
}

