#include "editorscene.h"

editorScene::editorScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    MyScene(x,y,width,height,parent)
{
    clickChess = new QMediaPlayer();
    clickChess->setMedia(QUrl("qrc:/audio/Audio/clickChess.mp3"));
    clickBoard = new QMediaPlayer();
    clickBoard->setMedia(QUrl("qrc:/audio/Audio/clickBoard.mp3"));
    killSound = new QMediaPlayer();
    killSound->setMedia(QUrl("qrc:/audio/Audio/killSound.mp3"));
    blackTurn = false;//white first
    waitNextStep = false;
    startPlay = false;
    K1 = false;
    K2 = false;
    R1 = false;
    R2 = false;
    R3 = false;
    R4 = false;
    win = 2;
    last_x = -1;
    last_y = -1;
    init_x = 0;
    init_y = 0;
    int count = 0;
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            grid[i][j] = new MyItem;
            grid[i][j]->x = i;
            grid[i][j]->y = j;
            grid[i][j]->side = 2;
            grid[i][j]->status = 0;
            if(count%2 == 0){
                grid[i][j]->isDark = false;
            }
            else {
                grid[i][j]->isDark = true;
            }
            count++;
        }
        count++;
    }
    init();
    whoseTurn->hide();

    Temp = new MyItem();
    this->addItem(Temp);
    Temp->hide();

    Blank[0] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Bg_Light"));
    Blank[1] = new QGraphicsPixmapItem(QPixmap(":/gridImg/posi"));
    Blank[2] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Bg_Dark"));
    Blank[0]->setPos(800,600);
    Blank[1]->setPos(800,700);
    Blank[2]->setPos(900,600);
    this->addItem(Blank[0]);
    this->addItem(Blank[1]);
    this->addItem(Blank[2]);

    Ch[0][0] = new QGraphicsPixmapItem(QPixmap(":/gridImg/King_W_L"));
    Ch[0][1] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Queen_W_D"));
    Ch[0][2] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Bishop_W_L"));
    Ch[0][3] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Knight_W_D"));
    Ch[0][4] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Rook_W_L"));
    Ch[0][5] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Pawn_W_D"));

    Ch[1][0] = new QGraphicsPixmapItem(QPixmap(":/gridImg/King_B_D"));
    Ch[1][1] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Queen_B_L"));
    Ch[1][2] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Bishop_B_D"));
    Ch[1][3] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Knight_B_L"));
    Ch[1][4] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Rook_B_D"));
    Ch[1][5] = new QGraphicsPixmapItem(QPixmap(":/gridImg/Pawn_B_L"));

    for(int i=0;i<6;++i){
        Ch[0][i]->setPos(800,0+100*i);
        Ch[1][i]->setPos(900,0+100*i);
        this->addItem(Ch[0][i]);
        this->addItem(Ch[1][i]);
        Ch[0][i]->show();
        Ch[1][i]->show();
    }
    stroke = new QGraphicsPixmapItem(QPixmap(":/gridImg/Stroke"));
    redStroke = new QGraphicsPixmapItem(QPixmap(":/gridImg/redStroke"));
    for(int i=0;i<16;++i){
       bStroke[i] = new QGraphicsPixmapItem(QPixmap(":/gridImg/blueStroke"));
       this->addItem(bStroke[i]);
       bStroke[i]->hide();
    }
    hover = new QGraphicsPixmapItem(QPixmap(":/gridImg/Hover"));
    this->addItem(stroke);
    this->addItem(redStroke);
    this->addItem(hover);
    stroke->hide();
    redStroke->hide();
    hover->hide();
}

void editorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pt = event->scenePos();
    //qDebug()<<"released ("<<pt.x()<<","<<pt.y()<<")";
    int x,y;
    findBox(x,y,pt);
    if(x==9 && y==7){
        ReEdit();
    }
    if(x==8 && y==7){
        startPlay = true;
    }
    else{
        if(noTouch) return;
        if(x<8){
            if(grid[x][y]->side == 2){
                if(clickBoard->state() == QMediaPlayer::PlayingState){
                    clickBoard->setPosition(0);
                }
                else if(clickBoard->state() == QMediaPlayer::StoppedState){
                    clickBoard->play();
                }
            }
            else {
                if(clickChess->state() == QMediaPlayer::PlayingState){
                    clickChess->setPosition(0);
                }
                else if(clickChess->state() == QMediaPlayer::StoppedState){
                    clickChess->play();
                }
            }
            if(startPlay){
                stroke->show();
                if(waitNextStep){
                    nextStep(x,y);
                }
                else{
                    stroke->setPos(x*100,y*100);
                    showPossible(x,y);
                }
                this->update();
            }
            else{
                stroke->show();
                if(waitNextStep){
                    grid[x][y]->side = Temp->side;
                    grid[x][y]->status = Temp->status;
                    grid[x][y]->setImg();
                    waitNextStep = false;
                    stroke->setPos(x*100,y*100);
                }
                this->update();
            }
        }
        else {
            if(clickBoard->state() == QMediaPlayer::PlayingState){
                clickBoard->setPosition(0);
            }
            else if(clickBoard->state() == QMediaPlayer::StoppedState){
                clickBoard->play();
            }
            stroke->show();
            if(!startPlay){
                if(!waitNextStep){
                    stroke->setPos(x*100,y*100);
                    if(y>5){
                        Temp->side = 2;
                        Temp->status = 0;
                    }
                    else{
                        Temp->side = x-8;
                        Temp->status = y+1;
                    }
                    qDebug()<<"side:"<<Temp->side<<"status:"<<Temp->side;
                    waitNextStep = true;
                }
            }
            this->update();
        }
    }


}

void editorScene::init()
{
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            grid[i][j]->setImg();
            grid[i][j]->setPosition();
            this->addItem(grid[i][j]);
        }
    }
}

void editorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"move: ("<<event->scenePos()<<")";
    if(noTouch) return;
    int x,y;
    findBox(x,y,event->scenePos());
    hover->show();
    hover->setPos(x*100,y*100);
    this->update();
}

void editorScene::ReEdit()
{
    blackTurn = false;//white first
    noTouch = false;
    waitNextStep = false;
    K1 = false;
    K2 = false;
    R1 = false;
    R2 = false;
    R3 = false;
    R4 = false;
    win = 2;
    int count = 0;
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            grid[i][j] = new MyItem;
            grid[i][j]->x = i;
            grid[i][j]->y = j;
            grid[i][j]->side = 2;
            grid[i][j]->status = 0;
            if(count%2 == 0){
                grid[i][j]->isDark = false;
            }
            else {
                grid[i][j]->isDark = true;
            }
            count++;
        }
        count++;
    }
    init();
}
