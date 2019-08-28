#define QT_NO_OPENGL
#ifndef SNAKE_H
#define SNAKE_H

#include<QVector>
#include <QFrame>
#include<QTime>
#include <QtGlobal>    //get random data
#include<QPainter>
#include"unit.h"
#include"environment.h"




class Snake: public environment
{
    //Q_OBJECT
    const int FOODNUMBER=1;            //food amount is not changed
    const int SNAKELENGTH=3;
    const int SNAKEHEADX=40;
    const int SNAKEHEADY=30;

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
private:
    DIRECTION Sdirection;

};

#endif // SNAKE_H
