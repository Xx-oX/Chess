#ifndef EDITORSCENE_H
#define EDITORSCENE_H
#include "myitem.h"
#include "myscene.h"

class editorScene : public MyScene
{
    Q_OBJECT
public:
    explicit editorScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

private:
    void init();
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void ReEdit();
    QGraphicsPixmapItem *Ch[2][6];
    QGraphicsPixmapItem *Blank[3];
    bool startPlay;
    MyItem *Temp;
};

#endif // EDITORSCENE_H
