#include "snake.h"
#include <QDebug>
#include "unit.h"
Snake::Snake(int sheadx,int sheady,int scolor,DIRECTION sdirection,THEME theme)
{
    this->snakeheadx=sheadx;
    this->snakeheady=sheady;
    this->snakecolor=scolor;
    this->Sdirection=sdirection;
    this->theme=theme;
}


void Snake::initSnake()
{
    QVsnake.clear();
    if(Sdirection==RIGHT){
    for (int i=0;i<SNAKELENGTH;++i) {
        QVsnake.append(Unit(snakeheadx-i,snakeheady,snakecolor));
    }
    }
    if(Sdirection==LEFT)
    {
        for (int i=0;i<SNAKELENGTH;++i) {
            QVsnake.append(Unit(snakeheadx+i,snakeheady,snakecolor));
    }
    }
    changeLock=true;
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
        default: break;
    }
}

/*grow*/
void Snake::QSgrow()
{
    QVsnake.append(Unit(snakeheadx,snakeheady,snakecolor));

}

/*judge eating using the head of snake*/
int Snake::QSeat(QVector<Unit> virtualFood)
{
    for(int i=0;i<virtualFood.size();++i)
    {
        if(QVsnake[0].getUnitX()==virtualFood[i].getUnitX()&&QVsnake[0].getUnitY()==virtualFood[i].getUnitY())
        {
            return i;
        }
    }
    return -1;
}

/* judge the snake is alive or not*/
bool Snake::QSalive(QVector<Unit> virtualBrick)
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
    for(int i=0;i<virtualBrick.size();++i)
    {
        if(headx==virtualBrick[i].getUnitX()&&heady==virtualBrick[i].getUnitY())
        {

            return false;
        }
    }
    return true;
}

/*change direction*/
void Snake::QSchangeDirection(DIRECTION direction)
{
    if(changeLock==true)
    {
        if((Sdirection+direction)!=3)   //sum of new and previous directioin equals to 3 means the directions are opposite;
        {
            Sdirection=direction;
        }
        changeLock=false;
    }
}

/*draw snake and food*/
void Snake::Qshow(QPainter &painter,int squarewidth, int squareheight,int boardLeft,int boardTop)
{
     if(ishiding==false)
     {
        for(int i=0;i<QVsnake.size();++i)
        {
            drawSquare(painter,boardLeft+QVsnake[i].getUnitX()*squarewidth,boardTop+QVsnake[i].getUnitY()*squareheight,QVsnake[i].getUnitColor(),squarewidth,squareheight);
        }
     }
    ishiding=false;
}

/*draw brick and food*/

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

int Snake::capture(QVector<Unit> initialSnake)
{
    int captureresult=-1;
    for(int i=0;i<initialSnake.size();++i)
    {
        if(initialSnake[i].getUnitX()==QVsnake[0].getUnitX()&&initialSnake[i].getUnitY()==QVsnake[0].getUnitY())
        {
            if(i==0)
            {
                captureresult=0;
            }
            else{
                captureresult=initialSnake.size()+1-i;
            }
        }
    }
    return captureresult;
}

bool Snake::QSquickGrow(int size)
{
    if(size<=0)
        return false;
    int current_size=QVsnake.size();
    int prevposx=QVsnake[current_size-2].getUnitX();
    int prevposy=QVsnake[current_size-2].getUnitY();
    int posx=QVsnake[current_size-1].getUnitX();
    int posy=QVsnake[current_size-1].getUnitY();
    int addx,addy;
    for(int i=1;i<=size;++i)
    {
        addx=posx+i*(posx-prevposx);
        addy=posy+i*(posy-prevposy);
        Unit unit(addx,addy,snakecolor);
        QVsnake.append(unit);
    }
    return true;
}

bool Snake::QSquickShort(int size)
{
    if(size>=QVsnake.size()-1)
        return false;
    for(int i=0;i<size;++i)
    {
        QVsnake.pop_back();
    }
    return true;
}

void Snake::hide()
{
    ishiding=true;
}
