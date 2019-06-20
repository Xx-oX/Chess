#include "theme.h"
#include "ui_theme.h"

theme::theme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::theme)
{
    ui->setupUi(this);
}

theme::~theme()
{
    delete ui;
}


void theme::on_classic_clicked()
{
    emit send(1);
}

void theme::on_newspaper_clicked()
{
    emit send(2);
}

void theme::on_bit_clicked()
{
    emit send(3);
}

