#include "promotion.h"
#include "ui_promotion.h"

promotion::promotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::promotion)
{
    ui->setupUi(this);
}

promotion::~promotion()
{
    delete ui;
}

void promotion::on_QueenButton_clicked()
{
    emit send(1);
    this->hide();
}

void promotion::on_BishopButton_clicked()
{
    emit send(2);
    this->hide();
}

void promotion::on_KnightButton_clicked()
{
    emit send(3);
    this->hide();
}

void promotion::on_RookButton_clicked()
{
    emit send(4);
    this->hide();
}
