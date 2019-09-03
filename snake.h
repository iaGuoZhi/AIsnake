#define QT_NO_OPENGL
#ifndef SNAKE_H
#define SNAKE_H

#include<QVector>
#include <QFrame>
#include<QTime>
#include <QtGlobal>
#include<QPainter>
#include"unit.h"
#include "shareinfo.h"
#include "environment.h"



class Snake
{
    /*作为友元，可直接访问environment中的私有成员*/
    friend class environment;


    //Q_OBJECT
    const int SNAKELENGTH=3;


public:
    Snake(int sheadx,int sheady,int scolor,DIRECTION sdirection,THEME theme);
    void initSnake();
    void QSmove();

    /* there three kinds of return type:
     * 0-----not eat
     * 1-----normal eat
     * 2-----eat hide buff
     * ********/
    int QSeat(QVector<Unit> virturalFood);
    void QSgrow();
    bool QSalive(QVector<Unit> virtualBrick);
    void hide();
    bool QSquickGrow(int size);
    bool QSquickShort(int size);
    void QSchangeDirection(DIRECTION direction);
    void Qshow(QPainter &painter,int squarewidth,int squareheight,int boardLeft,int boardTop);
    void drawUnit(QPainter &painter,int x,int y,UNITKIND unitkind,int squarewidth,int squareheight);
    void openChangeLock(){changeLock=true;}

    /* return type: -1 not captured,0-n the index of the snake,0 means head*/
    int capture(QVector<Unit> initialSnake);

     QVector<Unit> QVsnake;
protected:

    DIRECTION Sdirection;
    bool ishiding=false;
    int snakeheadx;
    int snakeheady;
    int snakecolor;
    bool changeLock;
    THEME theme=THEME::COSTOM_FOREST;



};

#endif // SNAKE_H
