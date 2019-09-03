#include "environment.h"

#include "unit.h"
#include<QDebug>

environment::environment(THEME theme,DIFFICULTY difficulty)
{
    this->theme=theme;
    this->difficulty=difficulty;

}

void environment::initEnvironment()
{
    createBrick();
    createFood();
}
void environment::createFood()
{
    QVfood.clear();
    for(int i=0;i<FOODNUMBER;++i)
    {
        QVfood.append(Unit(0,0,2,UNITKIND::FOODNORMAL));
        createFood(i);
    }
}

void environment::createFood(int index)
{
    int randomx,randomy;
    bool overlapflag=false;               //judge new created food's position is overlaped or not
    while(true)
    {
        overlapflag=false;
        qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
        randomx=qrand()%(BOARDWIDTH-4)+2;
        randomy=qrand()%(BOARDHEIGHT-4)+2;
        for(int j=0;j<QVfood.size();++j)
        {
            if(QVfood[j].getUnitX()==randomx&&QVfood[j].getUnitY()==randomy)
            {
                overlapflag=true;                   //avoid new created food is overlaped with other food
            }
        }
        for(int j=0;j<QVfoodbrick.size();++j)
        {
            if(QVfoodbrick[j].getUnitX()<=randomx&&QVfoodbrick[j].getUnitX()+BRICKWIDTH>=randomx&&QVfoodbrick[j].getUnitY()<=randomy&&QVfoodbrick[j].getUnitY()+BRICKHEIGHT>=randomy)
                overlapflag=true;
        }
        for(int i=0;i<QVbrick.size();++i)
        {
            if(QVbrick[i].getUnitX()==randomx&&QVbrick[i].getUnitY()==randomy)
            {
                overlapflag=true;
            }
        }
        if(overlapflag==false)
        {
            QVfood[index].setUnitX(randomx);
            QVfood[index].setUnitY(randomy);
            if(qrand()%7==0)
            {
                QVfood[index].setUnitColor(4);
                QVfood[index].setUnitDescribe("hideBuff");
                QVfood[index].setUnitKind(UNITKIND::FOODSPECIAL);
            }
            return;
        }                                     //circulate till the right position is created
    }
}

/* create brick as initial terrain*/
void environment::createBrick()
{
    QVbrick.clear();
    QVfoodbrick.clear();
    int random;
    createBorder();
    for(int i=1;i<BOARDWIDTH-BRICKWIDTH;++i)
    {
        for(int j=1;j<BOARDHEIGHT-BRICKHEIGHT;++j)
        {
            if(i>BOARDWIDTH/3&&2*i<BOARDWIDTH*4/3&&j>BOARDHEIGHT/3&&2*j<BOARDHEIGHT*4/3)
                continue;
            qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
            random=rand()%(500-100*difficulty);
            if(random==0)
            {
                QVfoodbrick.append(Unit(i,j,3,UNITKIND::BRICK));
                for(int k=0;k<BRICKWIDTH;++k)
                {
                    for(int t=0;t<BRICKHEIGHT;++t)
                    {
                        if(rand()%10>3)
                         QVbrick.append(Unit(i+k,j+t,3,UNITKIND::BRICK));
                    }
                }
            }
        }
    }
}

void environment::createBorder()
{
    for(int i=0;i<BOARDWIDTH;++i)
    {
        QVbrick.append(Unit(i,0,3,UNITKIND::BRICK));
        QVbrick.append(Unit(i,BOARDHEIGHT-1,3,UNITKIND::BRICK));
    }
    for(int i=0;i<BOARDHEIGHT;++i)
    {
        QVbrick.append(Unit(0,i,3,UNITKIND::BRICK));
        QVbrick.append(Unit(BOARDWIDTH-1,i,3,UNITKIND::BRICK));
    }
}

/*draw brick and food*/

void environment::drawSquare(QPainter &painter, int x, int y, int shape,int squarewidth,int squareheight)
{
    static const QRgb colorTable[8] = {
        0x000000, //black
        0xCC6666, //red
        0x66CC66, //green
        0x6666CC, //blue
        0xCCCC66, //red
        0xCC66CC, //purple
        0x66CCCC, //light blue
        0xDAAA00  //yellow
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

    /*QImage image(":/images/stone.png");
    painter.drawImage(x,y,image,0,0,squarewidth,squareheight);*/
}

void environment::drawUnit(QPainter &painter, int x, int y, UNITKIND unitKind, int squarewidth, int squareheight)
{
    if(unitKind==UNITKIND::BRICK)
    {
        int unitColor=0;
        switch (this->theme) {
        case THEME::COSTOM_FOREST:
            unitColor=3;
            break;
        case THEME::COSTOM_PIRARIE:
            unitColor=7;
            break;
        case THEME::COSTOM_SEA:
            unitColor=3;
            break;
        case THEME::SYSTEM_FUSION:
            unitColor=6;
            break;
        case THEME::SYSTEM_WINDOWS:
            unitColor=5;
            break;
        default:
            break;
        }
        drawSquare(painter,x,y,unitColor,squarewidth,squareheight);
        return;
    }
    else{
        if(unitKind==UNITKIND::FOODNORMAL)
        {
            QImage image(":/images/mush1.png");
            painter.drawImage(x,y,image,0,0,squarewidth,squareheight);
        }
        else{
            QImage image(":/images/mush2.png");
            painter.drawImage(x,y,image,0,0,squarewidth,squareheight);
        }
    }
}

/*draw food and brick*/
void environment::Qshow(QPainter &painter,int squarewidth, int squareheight,int boardLeft,int boardTop)
{
    for(int i=0;i<QVbrick.size();++i)
    {
        drawUnit(painter,boardLeft+QVbrick[i].getUnitX()*squarewidth,boardTop+QVbrick[i].getUnitY()*squareheight,QVbrick[i].getUnitKind(),squarewidth,squareheight);
    }
    for(int i=0;i<QVfood.size();++i)
    {
        drawUnit(painter,boardLeft+QVfood[i].getUnitX()*squarewidth,boardTop+QVfood[i].getUnitY()*squareheight,QVfood[i].getUnitKind(),squarewidth,squareheight);
    }
}

bool environment::isHideBuff(int index)
{
    if(index<0||index>QVfood.size())
        return false;
    if(QVfood[index].getUnitDescribe()=="hideBuff")
        return true;
    else
        return false;
}
