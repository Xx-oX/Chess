#include "start.h"
#include "ui_start.h"

start::start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    setWindowTitle(tr("Chess by 0_o"));
    setStyleSheet( "background-image:url(:/stratImg/startImg);" );
}

start::~start()
{
    delete ui;
}
void start::on_editorButton_clicked()
{
    Dialog *editor = new Dialog(1,this);
    extern int isEditor;
    isEditor = 2;
    editor->show();
}

void start::on_optionButton_clicked()
{
    //QMessageBox::information(this,tr("About"),tr("Author: 0_o\nDescription:\nThis is a Chess Game.\nHave Fun!!!"));
    extern int isEditor;
    isEditor = 1;

    QString defaultIp;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){
             qDebug() << address.toString();
             defaultIp = address.toString();
             break;
        }
    }
    qDebug()<<"defaultIp:"<<defaultIp;
    bool isC = true;
    QString text = QInputDialog::getText(this, "Server or Client",
                     "Please input Ip, press ok if is client, cancel if is server.",
                      QLineEdit::Normal, defaultIp, &isC);

        bool bServer = false;
        if(!isC)
        {
            bServer = true;
        }
    Dialog *NetGame = new Dialog(2,this,bServer,text);
    NetGame->show();
}
