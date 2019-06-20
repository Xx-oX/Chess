#include "myscene.h"
#include "mainwindow.h"


MyScene::MyScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x,y,width,height,parent)
{
    initial();
}

void MyScene::initial()
{
    rec = 0;
    clickChess = new QMediaPlayer();
    clickChess->setMedia(QUrl("qrc:/audio/Audio/clickChess.mp3"));
    clickBoard = new QMediaPlayer();
    clickBoard->setMedia(QUrl("qrc:/audio/Audio/clickBoard.mp3"));
    killSound = new QMediaPlayer();
    killSound->setMedia(QUrl("qrc:/audio/Audio/killSound.mp3"));

    extern int themeNum;
    switch(themeNum){
    case 1:
        board = new QGraphicsPixmapItem(QPixmap(":/gridImg/Image/bg_Clasic.png"));
        break;
    case 2:
        board = new QGraphicsPixmapItem(QPixmap(":/gridImg/newsPaper/Image/newspaper/bg_Newpaper.png"));
        break;
    case 3:
        board = new QGraphicsPixmapItem(QPixmap(":/gridImg/8bit/Image/8_bit/bg_8bit.png"));
        break;
    }

    board->setPos(0,0);
    this->addItem(board);
    board->show();


    blackTurn = false;//white first
    startTurn = blackTurn;
    noTouch = false;
    waitNextStep = false;
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
    extern int isEditor;
    //qDebug()<<isEditor;
    if(isEditor == 2)
    {
        for(int i=0;i<8;++i){
            for(int j=0;j<8;++j){
                grid[i][j] = new MyItem;
                grid[i][j]->x = i;
                grid[i][j]->y = j;
                grid[i][j]->side = 2;
                if(count%2 == 0){
                    grid[i][j]->isDark = false;
                }
                else {
                    grid[i][j]->isDark = true;
                }
            }
        }
        initBoard();
    }
    else if(isEditor == 1){
                for(int i=0;i<8;++i){
                    for(int j=0;j<8;++j){
                        grid[i][j] = new MyItem;
                        grid[i][j]->x = i;
                        grid[i][j]->y = j;
                        grid[i][j]->side = 2;
                        if(count%2 == 0){
                            grid[i][j]->isDark = false;
                        }
                        else {
                            grid[i][j]->isDark = true;
                        }

                        if(j==0 || j==1){
                             grid[i][j]->side = 1;
                             if(j==1) grid[i][j]->status = 6;//Pawn
                             else {
                                 switch (i){
                                    case 0:
                                     grid[i][j]->status = 5;//Rook
                                     break;
                                    case 1:
                                     grid[i][j]->status = 4;//Knight
                                     break;
                                    case 2:
                                     grid[i][j]->status = 3;//Bishop
                                     break;
                                    case 3:
                                     grid[i][j]->status = 2;//Queen
                                     break;
                                    case 4:
                                     grid[i][j]->status = 1;//King
                                     break;
                                    case 5:
                                     grid[i][j]->status = 3;
                                     break;
                                    case 6:
                                     grid[i][j]->status = 4;
                                     break;
                                    case 7:
                                     grid[i][j]->status = 5;
                                     break;
                                 }
                             }
                        }
                        else if(j==6 || j==7){
                             grid[i][j]->side = 0;
                             if(j==6) grid[i][j]->status = 6;//Pawn
                             else {
                                 switch (i){
                                    case 0:
                                     grid[i][j]->status = 5;//Rook
                                     break;
                                    case 1:
                                     grid[i][j]->status = 4;//Knight
                                     break;
                                    case 2:
                                     grid[i][j]->status = 3;//Bishop
                                     break;
                                    case 3:
                                     grid[i][j]->status = 2;//Queen
                                     break;
                                    case 4:
                                     grid[i][j]->status = 1;//King
                                     break;
                                    case 5:
                                     grid[i][j]->status = 3;
                                     break;
                                    case 6:
                                     grid[i][j]->status = 4;
                                     break;
                                    case 7:
                                     grid[i][j]->status = 5;
                                     break;
                                 }
                             }
                        }
                        else {
                             grid[i][j]->side = 2;
                             grid[i][j]->status = 0;
                        }
                    count++;
                    }count++;
                }
                initBoard();
    }
    else {
        for(int i=0;i<8;++i){
            for(int j=0;j<8;++j){
                grid[i][j] = new MyItem;
                grid[i][j]->x = i;
                grid[i][j]->y = j;
                grid[i][j]->side = 2;
                if(count%2 == 0){
                    grid[i][j]->isDark = false;
                }
                else {
                    grid[i][j]->isDark = true;
                }
            }
        }
    }
    stroke = new QGraphicsPixmapItem(QPixmap(":/gridImg/Stroke"));
    redStroke = new QGraphicsPixmapItem(QPixmap(":/gridImg/redStroke"));
    for(int i=0;i<16;++i){
       bStroke[i] = new QGraphicsPixmapItem(QPixmap(":/gridImg/blueStroke"));
       this->addItem(bStroke[i]);
       bStroke[i]->hide();
    }
    hover = new QGraphicsPixmapItem(QPixmap(":/gridImg/Hover"));
    whoseTurn = new QGraphicsPixmapItem(QPixmap(":/sceneImg/Turn"));
    whoseTurn->setPos(800,650);
    fog = new QGraphicsPixmapItem(QPixmap(":/sceneImg/fog"));
    fog->setPos(0,0);
    posi = new QGraphicsPixmapItem(QPixmap(":/gridImg/posi"));
    Wwins = new QGraphicsPixmapItem(QPixmap(":/sceneImg/Wwins"));
    Bwins = new QGraphicsPixmapItem(QPixmap(":/sceneImg/Bwins"));
    Wwins->setPos(0,0);
    Bwins->setPos(50,500);
    this->addItem(stroke);
    this->addItem(redStroke);
    this->addItem(hover);
    this->addItem(whoseTurn);
    this->addItem(fog);
    this->addItem(posi);
    this->addItem(Wwins);
    this->addItem(Bwins);
    stroke->hide();
    redStroke->hide();
    hover->hide();
    fog->hide();
    posi->hide();
    Wwins->hide();
    Bwins->hide();

    replay = new QLabel();
    replay->setGeometry(900,700,100,100);
    replay->setStyleSheet("border-image: url(:/sceneImg/replay) 3 10 3 10;border-top: 3px transparent;border-bottom: 3px transparent; border-right: 10px transparent;border-left: 10px transparent;background = transparent");
    proxyPush = addWidget(replay);
    proxyPush->show();

    movieLabel = new QLabel();
    movieLabel->setGeometry(280,280,480,480);
    changeSide = new QMovie(":/movie/change");
    changeSide->setScaledSize(QSize(480,480));
    movieLabel->setMovie(changeSide);
    changeSide->start();
    movieLabel->setVisible(false);

    labelW = new QLabel();
    labelW->setGeometry(400-245,400-140,490,280);
    Wwin = new QMovie(":/movie/whiteWin");
    Wwin->setScaledSize(QSize(490,280));
    proxyChangeSide = addWidget(movieLabel);
    labelW->setMovie(Wwin);
    Wwin->start();
    labelW->setVisible(false);
    proxyW = addWidget(labelW);

    labelB = new QLabel();
    labelB->setGeometry(160,265,480,270);
    Bwin = new QMovie(":/movie/blackWin");
    Bwin->setScaledSize(QSize(480,270));
    labelB->setMovie(Bwin);
    Bwin->start();
    labelB->setVisible(false);
    proxyB = addWidget(labelB);

}

void MyScene::Restart()
{
    //qDebug()<<"Restart";
    blackTurn = !startTurn;//change side
    startTurn = blackTurn;
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
            grid[i][j]->possibleList.clear();
            if(j==0 || j==1){
                 grid[i][j]->side = 1;
                 if(j==1) grid[i][j]->status = 6;//Pawn
                 else {
                     switch (i){
                        case 0:
                         grid[i][j]->status = 5;//Rook
                         break;
                        case 1:
                         grid[i][j]->status = 4;//Knight
                         break;
                        case 2:
                         grid[i][j]->status = 3;//Bishop
                         break;
                        case 3:
                         grid[i][j]->status = 2;//Queen
                         break;
                        case 4:
                         grid[i][j]->status = 1;//King
                         break;
                        case 5:
                         grid[i][j]->status = 3;
                         break;
                        case 6:
                         grid[i][j]->status = 4;
                         break;
                        case 7:
                         grid[i][j]->status = 5;
                         break;
                     }
                 }
            }
            else if(j==6 || j==7){
                 grid[i][j]->side = 0;
                 if(j==6) grid[i][j]->status = 6;//Pawn
                 else {
                     switch (i){
                        case 0:
                         grid[i][j]->status = 5;//Rook
                         break;
                        case 1:
                         grid[i][j]->status = 4;//Knight
                         break;
                        case 2:
                         grid[i][j]->status = 3;//Bishop
                         break;
                        case 3:
                         grid[i][j]->status = 2;//Queen
                         break;
                        case 4:
                         grid[i][j]->status = 1;//King
                         break;
                        case 5:
                         grid[i][j]->status = 3;
                         break;
                        case 6:
                         grid[i][j]->status = 4;
                         break;
                        case 7:
                         grid[i][j]->status = 5;
                         break;
                     }
                 }
            }
            else {
                 grid[i][j]->side = 2;
                 grid[i][j]->status = 0;
            }
        count++;
        }count++;
    }
    initBoard();
    proxyB->setVisible(false);
    proxyW->setVisible(false);
    fog->hide();
    Bwins->hide();
    Wwins->hide();
    stroke->hide();
    redStroke->hide();
    for(int i=0;i<16;++i)
        bStroke[i]->hide();
    if(blackTurn)
        whoseTurn->setPos(800,50);
    else
        whoseTurn->setPos(800,650);
    whoseTurn->show();
}

void MyScene::initBoard()
{
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            grid[i][j]->setImg();
            grid[i][j]->setPosition();
            this->addItem(grid[i][j]);
        }
    }
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pt = event->scenePos();
    //qDebug()<<"released ("<<pt.x()<<","<<pt.y()<<")";
    int x,y;
    findBox(x,y,pt);
    click(x,y);
}

void MyScene::click(int x,int y)
{
    if(x<8){
        if(noTouch) return;
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
    else {
        if(x==9 && y==7)
            Restart();
    }
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"move: ("<<event->scenePos()<<")";
    if(noTouch) return;
    int x,y;
    findBox(x,y,event->scenePos());
    hover->show();
    if(x<8)
        hover->setPos(x*100,y*100);
    else
        hover->setPos(event->scenePos().x()-50,event->scenePos().y()-50);
    this->update();
}

void MyScene::findBox(int &x, int &y, QPointF pt)
{
    if(pt.x()<=1000 && pt.x()>=0 && pt.y()<=800 && pt.y()>=0 )
    {
        x = (pt.x()-init_x)/100;
        y = (pt.y()-init_y)/100;
        //qDebug()<<"x:"<<x<<"y:"<<y;
    }
    else{
        //qDebug()<<"outside";
    }
}

void MyScene::showPossible(int x,int y)
{
    if(blackTurn == grid[x][y]->side){
        last_x = x;
        last_y = y;
        findPossible(grid[x][y]);
        //qDebug()<<x<<","<<y<<"list: ";
        int k = 0;
        foreach(QPointF i, grid[x][y]->possibleList){
            //qDebug()<<i<<"  ";
            int a = i.x();
            int b = i.y();
            if(grid[a][b]->side == 2){
                grid[a][b]->side = 3;
                grid[a][b]->setImg();
            }
            if(grid[a][b]->side != grid[x][y]->side && grid[a][b]->side != 2 && grid[a][b]->side != 3){
                if(grid[a][b]->status == 1 ){
                    //check
                    redStroke->setPos(a*100,b*100);
                    redStroke->show();
                }
                else if(grid[x][y]->status!=6){
                    //qDebug()<<"k:"<<k;
                    bStroke[k]->setPos(a*100,b*100);
                    bStroke[k]->show();
                    k++;
                }
            }
        }
        if(grid[x][y]->status == 6){
            if(grid[x][y]->side == 0){
                if(x==7){
                    if(grid[x-1][y-1]->side == 1){
                        if(grid[x-1][y-1]->status == 1){
                            redStroke->setPos((x-1)*100,(y-1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x-1)*100,(y-1)*100);
                            bStroke[k]->show();
                            k++;
                        }
                    }
                }
                else if(x==0){
                    if(grid[x+1][y-1]->side == 1){
                        if(grid[x+1][y-1]->status == 1){
                            redStroke->setPos((x+1)*100,(y-1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x+1)*100,(y-1)*100);
                            bStroke[k]->show();
                            k++;
                        }
                    }
                }
                else{
                    if(grid[x+1][y-1]->side == 1){
                        if(grid[x+1][y-1]->status == 1){
                            redStroke->setPos((x+1)*100,(y-1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x+1)*100,(y-1)*100);
                            bStroke[k]->show();
                            k++;
                       }
                    }
                    if(grid[x-1][y-1]->side == 1){
                        if(grid[x-1][y-1]->status == 1){
                            redStroke->setPos((x-1)*100,(y-1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x-1)*100,(y-1)*100);
                            bStroke[k]->show();
                            k++;
                        }
                    }
                }

            }
            if(grid[x][y]->side == 1){
                if(x==7){
                    if(grid[x-1][y+1]->side == 0){
                        if(grid[x-1][y+1]->status == 1){
                            redStroke->setPos((x-1)*100,(y+1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x-1)*100,(y+1)*100);
                            bStroke[k]->show();
                            k++;
                        }
                    }
                }
                else if(x==0){
                    if(grid[x+1][y+1]->side == 0){
                        if(grid[x+1][y+1]->status == 1){
                            redStroke->setPos((x+1)*100,(y+1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x+1)*100,(y+1)*100);
                            bStroke[k]->show();
                            k++;
                        }
                    }
                }
                else{
                    if(grid[x+1][y+1]->side == 0){
                        if(grid[x+1][y+1]->status == 1){
                            redStroke->setPos((x+1)*100,(y+1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x+1)*100,(y+1)*100);
                            bStroke[k]->show();
                            k++;
                       }
                    }
                    if(grid[x-1][y+1]->side == 0){
                        if(grid[x-1][y+1]->status == 1){
                            redStroke->setPos((x-1)*100,(y+1)*100);
                            redStroke->show();
                        }
                        else{
                            bStroke[k]->setPos((x-1)*100,(y+1)*100);
                            bStroke[k]->show();
                            k++;
                        }
                    }
                }
            }
        }
        waitNextStep = true;
    }
    else {
        return;
    }
}

void MyScene::nextStep(int x, int y)
{
    if(last_x == x && last_y == y){
        stroke->setPos(x*100,y*100);
        for(int a=0;a<8;++a){
            for(int b=0;b<8;++b){
                if(grid[a][b]->side == 3){
                    grid[a][b]->side = 2;
                    grid[a][b]->setImg();
                    //qDebug()<<"clean";
                }
            }
        }
        for(int i=0;i<16;++i)
            bStroke[i]->hide();
        showPossible(x,y);
        if(!isChecked()){
            redStroke->hide();
        }
        this->update();
        return;
    }
    if(isValid(grid[last_x][last_y],grid[x][y])){
        updateGrid(grid[last_x][last_y],grid[x][y]);
        grid[x][y]->setImg();
        grid[last_x][last_y]->setImg();
        stroke->setPos(x*100,y*100);
        /*
        QElapsedTimer timer;
        timer.start();
        while(!timer.hasExpired(1000)) {
            proxyChangeSide->setVisible(true);
            //qDebug()<<"Expired";
        }
        proxyChangeSide->setVisible(false);
        */

        for(int a=0;a<8;++a){
            for(int b=0;b<8;++b){
                if(grid[a][b]->side == 3){
                    grid[a][b]->side = 2;
                    grid[a][b]->setImg();
                    //qDebug()<<"clean";
                }
            }
        }
        for(int i=0;i<16;++i)
            bStroke[i]->hide();

        grid[x][y]->possibleList.clear();
        //qDebug()<<"Turn:"<<blackTurn;
        if(isChecked()){
            //qDebug()<<"checked";
        }
        else{
            redStroke->hide();
        }
        this->update();
    }
    else{
        if(grid[x][y]->side == grid[last_x][last_y]->side){
            stroke->setPos(x*100,y*100);
            for(int a=0;a<8;++a){
                for(int b=0;b<8;++b){
                    if(grid[a][b]->side == 3){
                        grid[a][b]->side = 2;
                        grid[a][b]->setImg();
                        //qDebug()<<"clean";
                    }
                }
            }
            for(int i=0;i<16;++i)
                bStroke[i]->hide();
            if(!isChecked()) {
                redStroke->hide();
            }
            showPossible(x,y);
            this->update();
        }
    }
}

bool MyScene::isValid(MyItem *Be,MyItem *Af)
{
    bool re = false;

    if(Be->possibleList.isEmpty()) return false;

    foreach(QPointF i,Be->possibleList)
        if(QPointF(Af->x,Af->y) == i) re = true;

    if(Be->side != Af->side && Af->side != 2)
    {
        if(Be->status == 6){
            if((Af->x-Be->x) == 1 || (Af->x-Be->x) == -1)
                re = true;
        }
    }
    //qDebug()<<"re: "<<re;
    return re;
}

void MyScene::findPossible(MyItem *G)
{
    if(G->side == 2 || G->side == 3){
        return;
    }
    switch(G->status){
        case 1:
            //King
            if(!K2){
                if(!R1 && G->side == 1 && !isAttacked(4,0,1) && !isAttacked(3,0,1) && !isAttacked(2,0,1) && grid[1][0]->side == 2 && grid[2][0]->side == 2 && grid[3][0]->side == 2){
                    G->possibleList<<QPointF(2,0);
                }
                else if(!R2 && G->side == 1 && !isAttacked(4,0,1) && !isAttacked(5,0,1) && !isAttacked(6,0,1) && grid[5][0]->side == 2 && grid[6][0]->side == 2){
                    G->possibleList<<QPointF(6,0);
                }
            }
            if(!K1){
                if(!R3 && G->side == 0 && !isAttacked(4,7,0) && !isAttacked(5,7,0) && !isAttacked(6,7,0) && grid[5][7]->side == 2 && grid[6][7]->side == 2){
                    G->possibleList<<QPointF(6,7);
                }
                else if(!R4 && G->side == 0 && !isAttacked(4,7,0) && !isAttacked(3,7,0) && !isAttacked(2,7,0) && grid[1][7]->side == 2 && grid[2][7]->side == 2 && grid[3][7]->side == 2){
                    G->possibleList<<QPointF(2,7);
                }
            }
            for(int i=-1;i<2;++i){
                for(int j=-1;j<2;++j){
                    if(G->x+i >= 0 && G->y+j >= 0 && G->x+i < 8 && G->y+j < 8
                            && grid[G->x+i][G->y+j]->side != G->side)
                        G->possibleList<<QPointF(G->x+i,G->y+j);
                }
            }
            break;
        case 2:
            //Queen
            for(int i=-7;i<8;++i){
                if(G->x+i >= 0 & G->x+i < 8 && grid[G->x+i][G->y]->side != G->side && !isBlocked(G,G->x+i,G->y))
                    G->possibleList<<QPointF(G->x+i,G->y);
                if(G->y+i >= 0 & G->y+i < 8 && grid[G->x][G->y+i]->side != G->side && !isBlocked(G,G->x,G->y+i))
                    G->possibleList<<QPointF(G->x,G->y+i);
                if(G->x+i >= 0 && G->y+i >= 0 && G->x+i < 8 && G->y+i < 8
                        && grid[G->x+i][G->y+i]->side != G->side && !isBlocked(G,G->x+i,G->y+i))
                    G->possibleList<<QPointF(G->x+i,G->y+i);
                if(G->x+i >= 0 && G->y-i >= 0 && G->x+i < 8 && G->y-i < 8
                        && grid[G->x+i][G->y-i]->side != G->side && !isBlocked(G,G->x+i,G->y-i))
                    G->possibleList<<QPointF(G->x+i,G->y-i);
                //qDebug()<<"Q"<<i;
        }
            break;
        case 3:
            //Bishop
            for(int i=-7;i<8;++i){
                if(G->x+i >= 0 && G->y+i >= 0 && G->x+i < 8 && G->y+i < 8
                        && grid[G->x+i][G->y+i]->side != G->side && !isBlocked(G,G->x+i,G->y+i))
                    G->possibleList<<QPointF(G->x+i,G->y+i);
                if(G->x+i >= 0 && G->y-i >= 0 && G->x+i < 8 && G->y-i < 8
                        && grid[G->x+i][G->y-i]->side != G->side && !isBlocked(G,G->x+i,G->y-i))
                    G->possibleList<<QPointF(G->x+i,G->y-i);
            //qDebug()<<"B"<<i;
            }
            break;
        case 4:
            //Knight
            checkKnight(G->x,G->y);
            break;
        case 5:
            //Rook
            for(int i=-7;i<8;++i){
                if(G->x+i >= 0 & G->x+i < 8 && grid[G->x+i][G->y]->side != G->side && !isBlocked(G,G->x+i,G->y))
                    G->possibleList<<QPointF(G->x+i,G->y);
                if(G->y+i >= 0 & G->y+i < 8 && grid[G->x][G->y+i]->side != G->side && !isBlocked(G,G->x,G->y+i))
                    G->possibleList<<QPointF(G->x,G->y+i);
                //qDebug()<<"R"<<i;
            }
            break;
        case 6:
            //Pawn
            if(G->side == 0){
                if(G->y == 6){
                    if(grid[G->x][G->y-1]->side == 2)
                    G->possibleList<<QPointF(G->x,G->y-1)<<QPointF(G->x,G->y-2);//(x,5),(x,4)
                }
                else
                    G->possibleList<<QPointF(G->x,G->y-1);
            }else {
                if(G->y == 1){
                    if(grid[G->x][G->y+1]->side == 2)
                        G->possibleList<<QPointF(G->x,G->y+1)<<QPointF(G->x,G->y+2);//(x,2),(x,3)
                }
                else
                    G->possibleList<<QPointF(G->x,G->y+1);
            }
                break;
        }
}

void MyScene::checkKnight(int x, int y)
{
    int side = grid[x][y]->side;
    if((x+1)>=0 && (x+1)<8 && (y+2)>=0  && (y+2)<8){
        if(grid[x+1][y+2]->side != side){
            grid[x][y]->possibleList<<QPointF(x+1,y+2);
        }
    }
    if((x+2)>=0 && (x+2)<8 && (y+1)>=0  && (y+1)<8){
        if(grid[x+2][y+1]->side != side){
            grid[x][y]->possibleList<<QPointF(x+2,y+1);
        }
    }
    if((x+2)>=0 && (x+2)<8 && (y-1)>=0  && (y-1)<8){
        if(grid[x+2][y-1]->side != side){
            grid[x][y]->possibleList<<QPointF(x+2,y-1);
        }
    }
    if((x+1)>=0 && (x+1)<8 && (y-2)>=0  && (y-2)<8){
        if(grid[x+1][y-2]->side != side){
            grid[x][y]->possibleList<<QPointF(x+1,y-2);
        }
    }
    if((x-1)>=0 && (x-1)<8 && (y-2)>=0  && (y-2)<8){
        if(grid[x-1][y-2]->side != side){
            grid[x][y]->possibleList<<QPointF(x-1,y-2);
        }
    }
    if((x-2)>=0 && (x-2)<8 && (y-1)>=0  && (y-1)<8){
        if(grid[x-2][y-1]->side != side){
            grid[x][y]->possibleList<<QPointF(x-2,y-1);
        }
    }
    if((x-2)>=0 && (x-2)<8 && (y+1)>=0  && (y+1)<8){
        if(grid[x-2][y+1]->side != side){
            grid[x][y]->possibleList<<QPointF(x-2,y+1);
        }
    }
    if((x-1)>=0 && (x-1)<8 && (y+2)>=0  && (y+2)<8){
        if(grid[x-1][y+2]->side != side){
            grid[x][y]->possibleList<<QPointF(x-1,y+2);
        }
    }
}

void MyScene::RookMoved(int x, int y)
{
    if(y==0){
        if(x==0) R1=true;
        if(x==7) R2=true;
        else return;
    }
    if(y==7){
        if(x==7) R3=true;
        if(x==0) R4=true;
        else return;
    }
}

bool MyScene::isBlocked(MyItem *Be,int a,int b)
{
MyItem *Af = grid[a][b];
bool isBlocked = false;
switch(Be->status){
    case 2:
        //Queen
        if(Af->y == Be ->y){
            if((Af->x-Be->x)>0){
                for(int i=1;i<(Af->x-Be->x);++i){
                    if(grid[Be->x+i][Be->y]->side != 2) isBlocked = true;
                }
            }
          else if((Af->x-Be->x)<0){
                for(int i=1;i<(Be->x-Af->x);++i){
                    if(grid[Be->x-i][Be->y]->side != 2) isBlocked = true;
                }
         }
        }
        else if(Af->x == Be->x){
            if((Af->y-Be->y)>0){
                for(int i=1;i<(Af->y-Be->y);++i)
                    if(grid[Be->x][Be->y+i]->side != 2) isBlocked = true;
            }
            else if((Af->y-Be->y)<0){
                for(int i=1;i<(Be->y-Af->y);++i)
                    if(grid[Be->x][Be->y-i]->side != 2) isBlocked = true;
            }
        }
        else if((Af->x-Be->x)>0){
            if((Af->y-Be->y)>0){
                for(int i=1;i<(Af->x-Be->x);++i)
                    if(grid[Be->x+i][Be->y+i]->side != 2) isBlocked = true;
            }
            if((Af->y-Be->y)<0){
                for(int i=1;i<(Af->x-Be->x);++i)
                    if(grid[Be->x+i][Be->y-i]->side != 2) isBlocked = true;
            }
        }
        else if((Af->x-Be->x)<0){
            if((Af->y-Be->y)>0){
                for(int i=1;i<(Be->x-Af->x);++i){
                    if(grid[Be->x-i][Be->y+i]->side != 2) isBlocked = true;
                }
            }
            else {
                for(int i=1;i<(Be->x-Af->x);++i){
                    if(grid[Be->x-i][Be->y-i]->side != 2) isBlocked = true;
                }
            }
        }
        else return false;
        //qDebug()<<Be->x<<","<<Be->y<<"->"<<Af->x<<","<<Af->y<<"isB:"<<isBlocked;
        break;
    case 3:
        //Bishop
        if((Af->x-Be->x)>0){
            if((Af->y-Be->y)>0){
                for(int i=1;i<Af->x-Be->x;++i)
                    if(grid[Be->x+i][Be->y+i]->side != 2) isBlocked = true;
            }
            if((Af->y-Be->y)<0){
                for(int i=1;i<Af->x-Be->x;++i)
                    if(grid[Be->x+i][Be->y-i]->side != 2) isBlocked = true;
            }
        }
        else if((Af->x-Be->x)<0){
            if((Af->y-Be->y)>0){
                for(int i=1;i<Be->x-Af->x;++i)
                    if(grid[Be->x-i][Be->y+i]->side != 2) isBlocked = true;
            }
            else {
                for(int i=1;i<Be->x-Af->x;++i)
                    if(grid[Be->x-i][Be->y-i]->side != 2) isBlocked = true;
            }
        }
        else return false;
        //qDebug()<<"isB:"<<isBlocked;
        break;
    case 5:
        //Rook
        if((Af->x-Be->x)>0){
            for(int i=1;i<Af->x-Be->x;++i)
                if(grid[Be->x+i][Be->y]->side != 2) isBlocked = true;
        }
        else if((Af->x-Be->x)<0){
            for(int i=1;i<Be->x-Af->x;++i)
                if(grid[Be->x-i][Be->y]->side != 2) isBlocked = true;
        }
        else if((Af->y-Be->y)>0){
            for(int i=1;i<Af->y-Be->y;++i)
                if(grid[Be->x][Be->y+i]->side != 2) isBlocked = true;
        }
        else if((Af->y-Be->y)<0){
            for(int i=1;i<Be->y-Af->y;++i)
                if(grid[Be->x][Be->y-i]->side != 2) isBlocked = true;
        }
        else return false;
        //qDebug()<<"isB:"<<isBlocked;
        break;
    default:
        return false;
    }
return isBlocked;
}

bool MyScene::isChecked()
{
    bool checked = false;
    redStroke->hide();
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            nonCastlingPossible(grid[i][j]);
            int s = grid[i][j]->side;
            foreach(QPointF p, grid[i][j]->possibleList){
            int a = p.x();
            int b = p.y();
            if(grid[a][b]->side != s && grid[a][b]->side != 2 && grid[a][b]->side != 3 && grid[i][j]->side != 2 && grid[i][j]->side !=3 && grid[i][j]->status != 6){
                if(grid[a][b]->status == 1 ){
                    //check
                    checked = true;
                    //qDebug()<<i<<","<<j<<"c"<<a<<b;
                    //qDebug()<<grid[i][j]->side<<grid[i][j]->status;
                    redStroke->setPos(a*100,b*100);
                    redStroke->show();
                }
            }
        }
        if(grid[i][j]->status == 6){
            if(grid[i][j]->side == 0){
                if(i==7){
                    if(grid[i-1][j-1]->side == 1){
                        if(grid[i-1][j-1]->status == 1){
                            checked = true;
                            redStroke->setPos((i-1)*100,(j-1)*100);
                            redStroke->show();
                        }
                    }
                }
                else if(i==0){
                    if(grid[i+1][j-1]->side == 1){
                        if(grid[i+1][j-1]->status == 1){
                            checked = true;
                            redStroke->setPos((i+1)*100,(j-1)*100);
                            redStroke->show();
                        }
                    }
                }
                else{
                    if(grid[i+1][j-1]->side == 1){
                        if(grid[i+1][j-1]->status == 1){
                            checked = true;
                            redStroke->setPos((i+1)*100,(j-1)*100);
                            redStroke->show();
                        }
                    }
                    if(grid[i-1][j-1]->side == 1){
                        if(grid[i-1][j-1]->status == 1){
                            checked = true;
                            redStroke->setPos((i-1)*100,(j-1)*100);
                            redStroke->show();
                        }
                    }
                }
            }
            if(grid[i][j]->side == 1){
                if(i==7){
                    if(grid[i-1][j+1]->side == 0){
                        if(grid[i-1][j+1]->status == 1){
                            checked = true;
                            redStroke->setPos((i-1)*100,(j+1)*100);
                            redStroke->show();
                        }
                    }
                }
                else if(i==0){
                    if(grid[i+1][j+1]->side == 0){
                        if(grid[i+1][j+1]->status == 1){
                            checked = true;
                            redStroke->setPos((i+1)*100,(j+1)*100);
                            redStroke->show();
                        }
                    }
                }
                else{
                    if(grid[i+1][j+1]->side == 0){
                        if(grid[i+1][j+1]->status == 1){
                            checked = true;
                            redStroke->setPos((i+1)*100,(j+1)*100);
                            redStroke->show();
                        }
                    }
                    if(grid[i-1][j+1]->side == 0){
                        if(grid[i-1][j+1]->status == 1){
                            checked = true;
                            redStroke->setPos((i-1)*100,(j+1)*100);
                            redStroke->show();
                        }
                    }
                }
            }
        }

        }
    }
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            grid[i][j]->possibleList.clear();
        }
    }
    if(!checked) redStroke->hide();
    return checked;
}

void MyScene::nonCastlingPossible(MyItem *G)
{
    if(G->side == 2 || G->side == 3){
        return;
    }
    switch(G->status){
        case 1:
            //King
            for(int i=-1;i<2;++i){
                for(int j=-1;j<2;++j){
                    if(G->x+i >= 0 && G->y+j >= 0 && G->x+i < 8 && G->y+j < 8
                            && grid[G->x+i][G->y+j]->side != G->side)
                        G->possibleList<<QPointF(G->x+i,G->y+j);
                }
            }
            break;
        case 2:
            //Queen
            for(int i=-7;i<8;++i){
                if(G->x+i >= 0 & G->x+i < 8 && grid[G->x+i][G->y]->side != G->side && !isBlocked(G,G->x+i,G->y))
                    G->possibleList<<QPointF(G->x+i,G->y);
                if(G->y+i >= 0 & G->y+i < 8 && grid[G->x][G->y+i]->side != G->side && !isBlocked(G,G->x,G->y+i))
                    G->possibleList<<QPointF(G->x,G->y+i);
                if(G->x+i >= 0 && G->y+i >= 0 && G->x+i < 8 && G->y+i < 8
                        && grid[G->x+i][G->y+i]->side != G->side && !isBlocked(G,G->x+i,G->y+i))
                    G->possibleList<<QPointF(G->x+i,G->y+i);
                if(G->x+i >= 0 && G->y-i >= 0 && G->x+i < 8 && G->y-i < 8
                        && grid[G->x+i][G->y-i]->side != G->side && !isBlocked(G,G->x+i,G->y-i))
                    G->possibleList<<QPointF(G->x+i,G->y-i);
                //qDebug()<<"Q"<<i;
        }
            break;
        case 3:
            //Bishop
            for(int i=-7;i<8;++i){
                if(G->x+i >= 0 && G->y+i >= 0 && G->x+i < 8 && G->y+i < 8
                        && grid[G->x+i][G->y+i]->side != G->side && !isBlocked(G,G->x+i,G->y+i))
                    G->possibleList<<QPointF(G->x+i,G->y+i);
                if(G->x+i >= 0 && G->y-i >= 0 && G->x+i < 8 && G->y-i < 8
                        && grid[G->x+i][G->y-i]->side != G->side && !isBlocked(G,G->x+i,G->y-i))
                    G->possibleList<<QPointF(G->x+i,G->y-i);
            //qDebug()<<"B"<<i;
            }
            break;
        case 4:
            //Knight
            checkKnight(G->x,G->y);
            break;
        case 5:
            //Rook
            for(int i=-7;i<8;++i){
                if(G->x+i >= 0 & G->x+i < 8 && grid[G->x+i][G->y]->side != G->side && !isBlocked(G,G->x+i,G->y))
                    G->possibleList<<QPointF(G->x+i,G->y);
                if(G->y+i >= 0 & G->y+i < 8 && grid[G->x][G->y+i]->side != G->side && !isBlocked(G,G->x,G->y+i))
                    G->possibleList<<QPointF(G->x,G->y+i);
                //qDebug()<<"R"<<i;
            }
            break;
        case 6:
            //Pawn
            if(G->side == 0){
                if(G->y == 6){
                    if(grid[G->x][G->y-1]->side == 2)
                    G->possibleList<<QPointF(G->x,G->y-1)<<QPointF(G->x,G->y-2);//(x,5),(x,4)
                }
                else
                    G->possibleList<<QPointF(G->x,G->y-1);
            }else {
                if(G->y == 1){
                    if(grid[G->x][G->y+1]->side == 2)
                        G->possibleList<<QPointF(G->x,G->y+1)<<QPointF(G->x,G->y+2);//(x,2),(x,3)
                }
                else
                    G->possibleList<<QPointF(G->x,G->y+1);
            }
                break;
        }
}

bool MyScene::isAttacked(int x, int y, int s)
{
    bool attacked = false;
    //qDebug()<<"Hi"<<x<<y;

    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            nonCastlingPossible(grid[i][j]);
            foreach(QPointF p, grid[i][j]->possibleList){
            int a = p.x();
            int b = p.y();
            if(a == x && b == y){
                if(grid[a][b]->side != grid[i][j]->side && grid[i][j]->side != 2 && grid[i][j]->side !=3 && grid[i][j]->status != 6){
                    if(s != grid[i][j]->side){
                        //attacked
                        attacked = true;
                        //qDebug()<<"attacked"<<grid[i][j]->side<<i<<j<<"c"<<grid[a][b]->side<<a<<b;
                    }
                }
            }
        }
        if(grid[i][j]->status == 6){
            if(grid[i][j]->side == 0){
                if(i==7){
                    if(grid[i-1][j-1]->side == 1){
                        if(i-1==x && j-1==y){
                            attacked = true;
                        }
                    }
                }
                else if(i==0){
                    if(grid[i+1][j-1]->side == 1){
                        if(i+1==x && j-1==y){
                            attacked = true;
                        }
                    }
                }
                else{
                    if(grid[i+1][j-1]->side == 1){
                        if(i+1==x && j-1==y){
                            attacked = true;
                        }
                    }
                    if(grid[i-1][j-1]->side == 1){
                        if(i-1==x && j-1==y){
                            attacked = true;
                        }
                    }
                }
            }
            if(grid[i][j]->side == 1){
                if(i==7){
                    if(grid[i-1][j+1]->side == 0){
                        if(i-1==x && j+1==y){
                            attacked = true;
                        }
                    }
                }
                else if(i==0){
                    if(grid[i+1][j+1]->side == 0){
                        if(i+1==x && j+1==y){
                            attacked = true;
                        }
                    }
                }
                else{
                    if(grid[i+1][j+1]->side == 0){
                        if(i+1==x && j+1==y){
                            attacked = true;
                        }
                    }
                    if(grid[i-1][j+1]->side == 0){
                        if(i-1==x && j+1==y){
                            attacked = true;
                        }
                    }
                }
            }
        }

        }
    }
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            grid[i][j]->possibleList.clear();
        }
    }
    //qDebug()<<x<<y<<attacked;
    return attacked;
}

void MyScene::updateGrid(MyItem *Be,MyItem *Af)
{
    switch(Be->status){
        case 1:
            //King
            if(Af->x == 2 && Af->y == 0){
                castling(1);
                break;
            }
            if(Af->x == 6 && Af->y == 0){
                castling(2);
                break;
            }
            if(Af->x == 6 && Af->y == 7){
                castling(3);
                break;
            }
            if(Af->x == 2 && Af->y == 7){
                castling(4);
                break;
            }
            if(Af->side != Be->side && Af->side != 3){
                eat(Af);
                Af->side = Be->side;
                Af->status = Be->status;
                Be->side = 2;
                Be->status = 0;
                if(Be->side == 0) K1 = true;
                if(Be->side == 1) K2 = true;
            }
            else {
                Af->side = Be->side;
                Af->status = Be->status;
                Be->side = 2;
                Be->status = 0;
                if(Be->side == 0) K1 = true;
                if(Be->side == 1) K2 = true;
            }
            break;
        case 5:
            //Rook
            if(Af->side != Be->side && Af->side != 2){
                eat(Af);
                Af->side = Be->side;
                Af->status = Be->status;
                Be->side = 2;
                Be->status = 0;
                RookMoved(Be->x,Be->y);
            }
            else {
                Af->side = Be->side;
                Af->status = Be->status;
                Be->side = 2;
                Be->status = 0;
                RookMoved(Be->x,Be->y);
            }
            break;
        case 6:
            //Pawn
            if((Af->x - Be->x) == 1 || (Af->x - Be->x) == -1){
                if(Af->side != Be->side && Af->side != 3){
                    if(Be->side == 0){
                        if((Be->y - Af->y)==1){
                            if(Af->y==0){
                                eat(Af);
                                Af->side = Be->side;
                                Be->side = 2;
                                Be->status = 0;
                                promotion(Af);
                                //qDebug()<<"side"<<Af->side<<"status"<<Af->status;
                            }
                            else{
                                eat(Af);
                                Af->side = Be->side;
                                Af->status = Be->status;
                                Be->side = 2;
                                Be->status = 0;
                            }
                        }
                        else return;
                    }
                    else{
                        if((Af->y - Be->y)==1){
                            if(Af->y==7){
                                eat(Af);
                                Af->side = Be->side;
                                Be->side = 2;
                                Be->status = 0;
                                promotion(Af);
                                //qDebug()<<"side"<<Af->side<<"status"<<Af->status;
                            }
                            else{
                                eat(Af);
                                Af->side = Be->side;
                                Af->status = Be->status;
                                Be->side = 2;
                                Be->status = 0;
                            }
                        }
                        else return;
                    }
                }
                else return;
            }
            else if(Af->x == Be->x && Af->side == 3){
                if(Af->y==0 || Af->y==7){
                    Af->side = Be->side;
                    Be->side = 2;
                    Be->status = 0;
                    promotion(Af);
                    //qDebug()<<"side"<<Af->side<<"status"<<Af->status;
                }
                else {
                    Af->side = Be->side;
                    Af->status = Be->status;
                    Be->side = 2;
                    Be->status = 0;
                }
            }
            else return;
        break;
    default:
        if(Af->side != Be->side && Af->side != 2 && Af->side != 3){
            eat(Af);
            Af->side = Be->side;
            Af->status = Be->status;
            Be->side = 2;
            Be->status = 0;
        }
        else if(Af->side == 2 || Af->side == 3){
            Af->side = Be->side;
            Af->status = Be->status;
            Be->side = 2;
            Be->status = 0;
        }
        else return;
    }

    /*
    animation = new QPropertyAnimation(Be,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(100,100,Be->x,Be->y));
    animation->setEndValue(QRect(100,100,Af->x,Af->y));
    animation->start();
    */

    waitNextStep = false;
    blackTurn = !blackTurn;
    if(blackTurn){
        whoseTurn->setPos(800,50);
    }
    else {
        whoseTurn->setPos(800,650);
    }
    //qDebug()<<"moved!";
}

void MyScene::eat(MyItem *Af)
{
    if(killSound->state() == QMediaPlayer::PlayingState){
        killSound->setPosition(0);
    }
    else if(killSound->state() == QMediaPlayer::StoppedState){
        killSound->play();
    }
    if(Af->status == 1){//gameover
        if(blackTurn) {
            //qDebug()<<"Black Win!!";
            win = 1;
            whoseTurn->hide();
            proxyB->setVisible(true);
            fog->show();
            Bwins->show();
            noTouch = true;
        }
        else {
            //qDebug()<<"White Win!!";
            win = 0;
            whoseTurn->hide();
            proxyW->setVisible(true);
            fog->show();
            Wwins->show();
            noTouch = true;
        }
    }else {
        //qDebug()<<"eat";
    }
}

void MyScene::recieve(int a)
{
    rec = a;
    //qDebug()<<"rec="<<rec;
}

void MyScene::promotion(MyItem *Af)
{
    //qDebug()<<"promotion!!";
    class promotion *p = new class promotion();
    connect(p,SIGNAL(send(int)),this,SLOT(recieve(int)));
    p->exec();
    switch (rec){
    case 1:
        Af->status = 2;
        break;
    case 2:
        Af->status = 3;
        break;
    case 3:
        Af->status = 4;
        break;
    case 4:
        Af->status = 5;
        break;
    default:
        qDebug()<<"failed to recieve!!";
        break;
    }
}

void MyScene::castling(int type)
{
    switch (type) {
        case 1:
            grid[0][0]->side = 2;
            grid[0][0]->status = 0;
            grid[2][0]->side = 1;
            grid[2][0]->status = 1;
            grid[3][0]->side = 1;
            grid[3][0]->status = 5;
            grid[4][0]->side = 2;
            grid[4][0]->status = 0;

            grid[0][0]->setImg();
            grid[2][0]->setImg();
            grid[3][0]->setImg();
            grid[4][0]->setImg();
            K2 = true;
            R1 = true;
        break;
        case 2:
            grid[4][0]->side = 2;
            grid[4][0]->status = 0;
            grid[5][0]->side = 1;
            grid[5][0]->status = 5;
            grid[6][0]->side = 1;
            grid[6][0]->status = 1;
            grid[7][0]->side = 2;
            grid[7][0]->status = 0;

            grid[4][0]->setImg();
            grid[5][0]->setImg();
            grid[6][0]->setImg();
            grid[7][0]->setImg();
            K2 = true;
            R2 = true;

        break;
        case 3:
            grid[4][7]->side = 2;
            grid[4][7]->status = 0;
            grid[5][7]->side = 0;
            grid[5][7]->status = 5;
            grid[6][7]->side = 0;
            grid[6][7]->status = 1;
            grid[7][7]->side = 2;
            grid[7][7]->status = 0;

            grid[4][7]->setImg();
            grid[5][7]->setImg();
            grid[6][7]->setImg();
            grid[7][7]->setImg();
            K1 = true;
            R3 = true;
        break;
        case 4:
            grid[0][7]->side = 2;
            grid[0][7]->status = 0;
            grid[2][7]->side = 0;
            grid[2][7]->status = 1;
            grid[3][7]->side = 0;
            grid[3][7]->status = 5;
            grid[4][7]->side = 2;
            grid[4][7]->status = 0;

            grid[0][7]->setImg();
            grid[2][7]->setImg();
            grid[3][7]->setImg();
            grid[4][7]->setImg();
            K1 = true;
            R4 = true;
        break;
        default:
            return;
    }
    //qDebug()<<"Castling!!type:"<<type;
}

