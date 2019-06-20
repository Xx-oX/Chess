#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QColor>
#include <QList>
#include <QLabel>
#include <QElapsedTimer>
#include <QMovie>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include "myitem.h"
#include "promotion.h"

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
    int init_x,init_y,count;//init(x,y): initial draw point, count: decide draw or not
    int last_x,last_y;
    int win;//0:white 1:black 2:non
    int rec;
    bool blackTurn;//false: white turn
    bool startTurn;
    MyItem *grid[8][8];

    void initial();
    void click(int,int);
    void Restart();
    void initBoard();
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void showPossible(int x,int y);
    void nextStep(int x,int y);
    void findPossible(MyItem *G);
    void findBox(int &x,int &y,QPointF pt);
    void updateGrid(MyItem *Be,MyItem *Af);
    void checkKnight(int x,int y);
    void RookMoved(int x,int y);
    void eat(MyItem *Af);
    void promotion(MyItem *Af);
    void castling(int i);
    void nonCastlingPossible(MyItem *G);
    bool isValid(MyItem *Be,MyItem *Af);
    bool isBlocked(MyItem *Be,int a,int b);
    bool isChecked();
    bool isAttacked(int x,int y,int side);
    bool K1,K2,R1,R2,R3,R4;//K1:W,K2:B,R1:Rook(0,0),R2:Rook(7,0),R3:Rook(7,7),R4:Rook(0,7)
    bool waitNextStep;
    bool noTouch;
    //QList<QString> list_W,list_B;
    QPointF pt;
    QGraphicsPixmapItem *board;
    QGraphicsPixmapItem *stroke;
    QGraphicsPixmapItem *redStroke;
    QGraphicsPixmapItem *bStroke[16];
    QGraphicsPixmapItem *hover;
    QGraphicsPixmapItem *whoseTurn;
    QGraphicsPixmapItem *fog;
    QGraphicsPixmapItem *posi;
    QGraphicsPixmapItem *Wwins,*Bwins;
    QGraphicsProxyWidget *proxyChangeSide,*proxyW,*proxyB,*proxyPush;
    QLabel *movieLabel,*labelW,*labelB;
    QLabel *replay;
    QMovie *changeSide,*Wwin,*Bwin;
    QMediaPlayer *clickChess,*clickBoard,*killSound;
    QPropertyAnimation *animation;
private slots:
    void recieve(int);
};

#endif // MYSCENE_H
