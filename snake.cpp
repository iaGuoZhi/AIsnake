#include "snake.h"
#include <QDebug>
#include "unit.h"
Snake::Snake()
{
    initSnake();
}
void Snake::initSnake()
{
    /*create default initial snake*/
    createBrick();
    QVsnake.clear();
    for (int i=0;i<SNAKELENGTH;++i) {
        QVsnake.append(Unit(SNAKEHEADX-i,SNAKEHEADY,1));
    }
    Sdirection=RIGHT;
    QVfood.clear();
    for(int i=0;i<FOODNUMBER;++i)
    {
        QVfood.append(Unit(SNAKEHEADX,SNAKEHEADY,2));
    }     //初始化food，等待后面随机化

    /*create random food*/
    for(int i=0;i<FOODNUMBER;++i)
    {
       createFood(i);
    }

}

/* create food,to avoid the new food location is coincidly the body of snake,use a function */
void Snake::createFood(int index)
{
    int randomx,randomy;
    bool overlapflag=false;               //judge new created food's position is overlaped with snake's or not
    while(true)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        randomx=qrand()%BOARDWIDTH;
        randomy=qrand()%BOARDHEIGHT;
        for(int j=0;j<QVsnake.size();++j)
        {
            if(QVsnake[j].getUnitX()==randomx&&QVsnake[j].getUnitY()==randomy)
            {
                overlapflag=true;
            }
        }
        for(int j=0;j<QVfood.size();++j)
        {
            if(j==index)
                continue;
            if(QVfood[j].getUnitY()==randomx&&QVfood[j].getUnitY()==randomy)
                overlapflag=true;                   //avoid new created food is overlaped with other food
        }
        for(int j=0;j<QVfoodbrick.size();++j)
        {
            if(QVfoodbrick[j].getUnitX()<=randomx&&QVfoodbrick[j].getUnitX()+BRICKWIDTH>=randomx&&QVfoodbrick[j].getUnitY()<=randomy&&QVfoodbrick[j].getUnitY()+BRICKHEIGHT>=randomy)
                overlapflag=true;
        }
        if(overlapflag==false)
        {
            QVfood[index].setUnitX(randomx);
            QVfood[index].setUnitY(randomy);
            return;
        }                                     //circulate till the right position is created
    }
}

/* create brick as initial terrain*/
void Snake::createBrick()
{
    int random;
    for(int i=0;i<BOARDWIDTH-BRICKWIDTH;++i)
    {
        for(int j=0;j<BOARDHEIGHT-BRICKHEIGHT;++j)
        {
            if(i<=SNAKEHEADX&&i+BRICKWIDTH>=SNAKEHEADX&&j<=SNAKEHEADY&&j+BRICKHEIGHT>=SNAKEHEADY)
                continue;
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            random=rand()%300;
            if(random==0)
            {
                QVfoodbrick.append(Unit(i,j,3));
                for(int k=0;k<BRICKWIDTH;++k)
                {
                    for(int t=0;t<BRICKHEIGHT;++t)
                    {
                        if(rand()%3!=0)
                         QVbrick.append(Unit(i+k,j+t,3));
                    }
                }
            }
        }
    }
}

/*move snake due to direction*/
void Snake::QSmove(){
    for(int i=QVsnake.size()-1;i>0;--i)
    {
        QVsnake[i].setUnitX(QVsnake[i-1].getUnitX());
        QVsnake[i].setUnitY(QVsnake[i-1].getUnitY());
    }
    switch (Sdirection) {
       case LEFT:
            QVsnake[0].setUnitX(QVsnake[0].getUnitX()-1);
        break;
        case RIGHT:
             QVsnake[0].setUnitX(QVsnake[0].getUnitX()+1);
         break;
        case UP:
             QVsnake[0].setUnitY(QVsnake[0].getUnitY()-1);
         break;
        case DOWN:
             QVsnake[0].setUnitY(QVsnake[0].getUnitY()+1);
         break;
    }
}

/*grow*/
void Snake::QSgrow()
{
    QVsnake.append(Unit(SNAKEHEADX,SNAKEHEADY,1));
    QSmove();                   //wo don't need to specity the position of snake's rear because it will move
}

/*judge eating using the head of snake*/
bool Snake::QSeat()
{
    for(int i=0;i<QVfood.size();++i)
    {
        if(QVfood[i].getUnitX()==QVsnake[0].getUnitX()&&QVfood[i].getUnitY()==QVsnake[0].getUnitY())  //snake head
        {
            createFood(i);
            return true;
        }
    }
    return false;
}

/* judge the snake is alive or not*/
bool Snake::QSalive()
{
    int headx=QVsnake[0].getUnitX();
    int heady=QVsnake[0].getUnitY();
    for(int i=1;i<QVsnake.size();++i)
    {
        if(headx==QVsnake[i].getUnitX()&&heady==QVsnake[i].getUnitY())
        {
            return false;
        }
    }
    if(headx<0||headx>BOARDWIDTH||heady<0||heady>=BOARDHEIGHT)
    {
        return false;
    }
    for(int i=0;i<QVbrick.size();++i)
    {
        if(headx==QVbrick[i].getUnitX()&&heady==QVbrick[i].getUnitY())
        {
            return false;
        }
    }
    return true;
}

/*change direction*/
void Snake::QSchangeDirection(DIRECTION direction)
{
    if((Sdirection+direction)!=3)   //sum of new and previous directioin equals to 3 means the directions are opposite;
    {
        Sdirection=direction;
    }

}

/*draw snake and food*/
void Snake::Qshow(QPainter &painter,int squarewidth, int squareheight,int boardLeft,int boardTop)
{
        for(int i=0;i<QVbrick.size();++i)
        {
            drawSquare(painter,boardLeft+QVbrick[i].getUnitX()*squarewidth,boardTop+QVbrick[i].getUnitY()*squareheight,QVbrick[i].getUnitColor(),squarewidth,squareheight);
        }
        for(int i=0;i<QVsnake.size();++i)
        {
            drawSquare(painter,boardLeft+QVsnake[i].getUnitX()*squarewidth,boardTop+QVsnake[i].getUnitY()*squareheight,QVsnake[i].getUnitColor(),squarewidth,squareheight);
        }
        for(int i=0;i<QVfood.size();++i)
        {
            drawSquare(painter,boardLeft+QVfood[i].getUnitX()*squarewidth,boardTop+QVfood[i].getUnitY()*squareheight,QVfood[i].getUnitColor(),squarewidth,squareheight);
        }
}

void Snake::drawSquare(QPainter &painter, int x, int y, int shape,int squarewidth,int squareheight)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, squarewidth - 2, squareheight - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareheight - 1, x, y);
    painter.drawLine(x, y, x + squarewidth - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareheight - 1,
                     x + squarewidth - 1, y + squareheight - 1);
    painter.drawLine(x + squarewidth - 1, y + squareheight - 1,
                     x + squarewidth - 1, y + 1);
}
