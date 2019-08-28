/********
 * environment.h .c file is the define and implement of class environment
 * which is the parent of class singlesnake,doublesnake,aisnake,playwithaisnake
 * there are mainly two advantages of create this file.
 * first,use inheriance strategy,the four or more snake class can share common data
 * structure,data,function. besides,in this way,the relationship between
 * the whole snake class are more clear.
 * second,by defining and implementing function of food,brick in the environment.h .c
 * we can seperate snake with food and initial brick. which is benefit to
 * avoiding coupling
 *
 *
 * ******/
#define QT_NO_OPENGL
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include<QVector>
#include <QFrame>
#include<QTime>
#include <QtGlobal>    //get random data
#include<QPainter>
#include"unit.h"

enum{
    BOARDWIDTH=79,
    BOARDHEIGHT=60,
    BRICKWIDTH=7,
    BRICKHEIGHT=5
}; //set the amount of unit a board can hold
enum DIRECTION{
    RIGHT,DOWN,UP,LEFT
};

class environment: public QFrame  //继承qframe to enable the ability to draw
{
public:
    environment();
    QVector<Unit> QVfood;
    QVector<Unit> QVbrick;
    QVector<Unit> QVfoodbrick;       //array of the left-top point in the blocks of QVbrick, which can help generate food in the block;
    void drawSquare(QPainter &painter,int x,int y,int color,int squarewidth,int squareheight);
    void createFood(int index,QVector<Unit> virtualSnake);
    void createBrick();
    void createBorder();

};

#endif // ENVIRONMENT_H
