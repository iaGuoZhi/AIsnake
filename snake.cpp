#include "snake.h"
#include <QDebug>
#include "unit.h"
Snake::Snake()
{
    initSnake();
}
void Snake::initSnake()
{

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
       createFood(i,QVsnake);
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
int Snake::QSeat()
{
    int result=0;
    for(int i=0;i<QVfood.size();++i)
    {
        if(QVfood[i].getUnitX()==QVsnake[0].getUnitX()&&QVfood[i].getUnitY()==QVsnake[0].getUnitY())  //snake head
        {
            /* return 2 means snake eat a food which has a hidebuff*/
            if(QVfood[i].getUnitDescribe()=="hideBuff")
            {
                result=2;
            }
            else result=1;
            createFood(i,QVsnake);
            return result;
        }
    }
    return result;
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
    for(int i=0;i<QVfood.size();++i)
    {
        drawSquare(painter,boardLeft+QVfood[i].getUnitX()*squarewidth,boardTop+QVfood[i].getUnitY()*squareheight,QVfood[i].getUnitColor(),squarewidth,squareheight);
    }
     if(ishiding==false)
     {
        for(int i=0;i<QVsnake.size();++i)
        {
            drawSquare(painter,boardLeft+QVsnake[i].getUnitX()*squarewidth,boardTop+QVsnake[i].getUnitY()*squareheight,QVsnake[i].getUnitColor(),squarewidth,squareheight);
        }
     }
    ishiding=false;
}


void Snake::hide()
{
    ishiding=true;
}
