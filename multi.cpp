#include "multi.h"

Multi::Multi(QString ip,bool isServer,qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    MyScene (x,y,width,height,parent)
{
    server = NULL;
    socket = NULL;

    if(isServer){
        qDebug()<<"isServer!";
        server = new QTcpServer(this);
        server->listen(QHostAddress::Any,9487);
        connect(server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    }
    else {
    //is client
        qDebug()<<"isClient!";
        socket = new QTcpSocket(this);
        socket->connectToHost(QHostAddress(ip),9487);
        connect(socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
    }
}

void Multi::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pt = event->scenePos();
    //qDebug()<<"released ("<<pt.x()<<","<<pt.y()<<")";
    int x,y;
    findBox(x,y,pt);
    Cclick(x,y);
}

void Multi::Cclick(int x,int y)
{
    MyScene::click(x,y);
    char mes[3];
    mes[0] = 2;
    mes[1] = x;
    mes[2] = y;
    qDebug()<<"out"<<mes;
    socket->write(mes,3);

}

void Multi::slotRecv()
{
    QByteArray data = socket->readAll();
    qDebug()<<"Recv"<<data;
    int x = data[1];
    int y = data[2];
    qDebug()<<x<<y;
    MyScene::click(x,y);

}

void Multi::slotNewConnection()
{
    if(socket)
        return;

    socket = server->nextPendingConnection();
    qDebug()<<"connected!!";
    connect(socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
    initial();
}
