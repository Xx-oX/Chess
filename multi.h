#ifndef MULTI_H
#define MULTI_H
#include "myitem.h"
#include "myscene.h"
#include <QtNetwork>

class Multi : public MyScene
{
    Q_OBJECT
public:
    explicit Multi(QString ip,bool isServer,qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
    QTcpServer *server;
    QTcpSocket *socket;
    void Cclick(int,int);

signals:

public slots:
    void slotNewConnection();
    void slotRecv();
private:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MULTI_H
