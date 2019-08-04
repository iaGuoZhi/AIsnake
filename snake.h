#define QT_NO_OPENGL
#ifndef SNAKE_H
#define SNAKE_H

#include<QVector>
#include <QFrame>
#include<QTime>
#include <QtGlobal>    //get random data
#include<QPainter>
#include"unit.h"


enum{
    BOARDWIDTH=50,
    BOARDHEIGHT=36
}; //set the amount of unit a board can hold
enum DIRECTION{
    RIGHT,DOWN,UP,LEFT
};

class Snake: public QFrame             //继承qframe，to enable the ability to draw
{
    //Q_OBJECT
    const int FOODNUMBER=1;            //food amount is not changed
    const int SNAKELENGTH=3;
    const int SNAKEHEADX=25;
    const int SNAKEHEADY=20;
public:
    Snake();
    void initSnake();
    void QSmove();
    bool QSeat();
    void QSgrow();
    bool QSalive();
    void QSchangeDirection(DIRECTION direction);
    void Qshow(QPainter &painter,int squarewidth,int squareheight,int boardLeft,int boardTop);
    QVector<Unit> QVsnake;           //为了paint，暂时public
    QVector<Unit> QVfood;
    void drawSquare(QPainter &painter,int x,int y,int color,int squarewidth,int squareheight);
    DIRECTION Sdirection;
    void createFood(int index);
};

#endif // SNAKE_H
