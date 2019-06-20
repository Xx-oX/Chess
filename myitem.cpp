#include "myitem.h"
MyItem::MyItem(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    this->setAcceptHoverEvents(true);
}

void MyItem::setImg()
{
    extern int themeNum;
    //qDebug()<<"myitem "<<themeNum;
    switch(themeNum){
    case 1:
        classic();
        break;
    case 2:
        newspaper();
        break;
    case 3:
        bit();
        break;
    }
}
void MyItem::newspaper()
{
    if (side == 0){
        this->show();
        switch (status) {
        case 1:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/wk.png"));
            break;
        case 2:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/wq.png"));
            break;
        case 3:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/wb.png"));
            break;
        case 4:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/wn.png"));
            break;
        case 5:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/wr.png"));
            break;
        case 6:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/wp.png"));
            break;
        }
    }
    else if (side == 1){
        this->show();
        switch (status) {
        case 1:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/bk.png"));
            break;
        case 2:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/bq.png"));
            break;
        case 3:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/bb.png"));
            break;
        case 4:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/bn.png"));
            break;
        case 5:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/br.png"));
            break;
        case 6:
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/bp.png"));
            break;
        }
    }
    else if(side == 3){
        this->show();
        if(isDark){
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/posi_D.jpg"));
        }else {
            this->setPixmap(QPixmap(":/gridImg/newsPaper/Image/newspaper/posi_L.jpg"));
        }
    }
    else {
        this->hide();
    }
}


void MyItem::classic()
{
    if (side == 3){
        if(isDark)
            this->setPixmap(QPixmap(":/gridImg/possible_D"));
        else
            this->setPixmap(QPixmap(":/gridImg/possible_L"));
    }
    else if(side==2){
        if(isDark)
            this->setPixmap(QPixmap(":/gridImg/Bg_Dark"));
        else
            this->setPixmap(QPixmap(":/gridImg/Bg_Light"));
    }
    else if(side==0){
        switch(status){
            case 1:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/King_W_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/King_W_L"));
            break;
            case 2:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Queen_W_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Queen_W_L"));
            break;
            case 3:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Bishop_W_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Bishop_W_L"));
            break;
            case 4:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Knight_W_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Knight_W_L"));
            break;
            case 5:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Rook_W_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Rook_W_L"));
            break;
            case 6:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Pawn_W_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Pawn_W_L"));
            break;
        }
    }else {
        switch(status){
            case 1:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/King_B_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/King_B_L"));
            break;
            case 2:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Queen_B_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Queen_B_L"));
            break;
            case 3:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Bishop_B_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Bishop_B_L"));
            break;
            case 4:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Knight_B_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Knight_B_L"));
            break;
            case 5:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Rook_B_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Rook_B_L"));
            break;
            case 6:
                if(isDark)
                    this->setPixmap(QPixmap(":/gridImg/Pawn_B_D"));
                else
                    this->setPixmap(QPixmap(":/gridImg/Pawn_B_L"));
            break;
        }
}

}

void MyItem::bit()
{
    if (side == 0){
        this->show();
        switch (status) {
        case 1:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/wk.png"));
            break;
        case 2:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/wq.png"));
            break;
        case 3:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/wb.png"));
            break;
        case 4:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/wn.png"));
            break;
        case 5:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/wr.png"));
            break;
        case 6:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/wp.png"));
            break;
        }
    }
    else if (side == 1){
        this->show();
        switch (status) {
        case 1:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/bk.png"));
            break;
        case 2:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/bq.png"));
            break;
        case 3:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/bb.png"));
            break;
        case 4:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/bn.png"));
            break;
        case 5:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/br.png"));
            break;
        case 6:
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/bp.png"));
            break;
        }
    }
    else if(side == 3){
        this->show();
        if(isDark){
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/posi_D.png"));
        }else {
            this->setPixmap(QPixmap(":/gridImg/8bit/Image/8_bit/posi_L.png"));
        }
    }
    else {
        this->hide();
    }
}

void MyItem::setPosition()
{
    this->setPos(x*100,y*100);
}

