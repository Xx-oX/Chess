#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QDebug>

class MyItem :public QGraphicsPixmapItem
{
public:
    explicit MyItem(QGraphicsItem * parent = nullptr);
    int x;
    int y;
    bool isDark;
    int side;//0:white,1:black,2:non,3:possible
    int status;//{Empty = 0,King,Queen,Bishop,Knight,Rook,Pawn}
    QList<QPointF> possibleList;

    void setImg();
    void setPosition();
    void classic();
    void newspaper();
    void bit();

private:

};

#endif // MYITEM_H
