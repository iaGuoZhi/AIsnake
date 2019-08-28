#define QT_NO_OPENGL
#include "doublesnakeboard.h"
#include "QDebug"
#include <QKeyEvent>

doubleSnakeBoard::doubleSnakeBoard(QWidget *parent)
    : snakeboard(parent)
{
    init();
    score1=0;
    score2=0;
    level1=0;
    level2=0;
    timer.start(timeoutTime(),this);
}

void doubleSnakeBoard::start()
{
    state=RUN;
    snake1.initSnake();
    snake2.initSnake();
    emit score1Changed(score1);
    emit level1Changed(level1);
    emit score2Changed(score2);
    emit level2Changed(level2);
}

void doubleSnakeBoard::keyPressEvent(QKeyEvent *event)
{
    if(state!=RUN)
    {
        QFrame::keyPressEvent(event);
        return;
    }
    switch (event->key()) {
    case Qt::Key_Left:
        snake1.QSchangeDirection(LEFT);
        break;
    case Qt::Key_Right:
        snake1.QSchangeDirection(RIGHT);
        break;
    case Qt::Key_Down:
        snake1.QSchangeDirection(DOWN);
        break;
    case Qt::Key_Up:
        snake1.QSchangeDirection(UP);
        break;
    case Qt::Key_A:
        snake2.QSchangeDirection(LEFT);
        break;
    case Qt::Key_D:
        snake2.QSchangeDirection(RIGHT);
        break;
    case Qt::Key_S:
        snake2.QSchangeDirection(DOWN);
        break;
    case Qt::Key_W:
        snake2.QSchangeDirection(UP);
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void doubleSnakeBoard::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timer.timerId()){
        if(state==RUN&&command!=HELP)
        {
            snake1.QSmove();
            snake2.QSmove();
            if(snake1.QSeat())
            {
                score1+=3;
                level1=score1/10;
                snake1.QSgrow();
                emit score1Changed(score1);
                emit level1Changed(level1);
            }
            if(snake2.QSeat())
            {
                score2+=3;
                level2=score2/10;
                snake2.QSgrow();
                emit score2Changed(score2);
                emit level2Changed(level2);
            }
            if(!snake1.QSalive()||!snake2.QSalive())
            {
                state=END;
            }
            update();
        }
        if(command==HELP)
        {
            update();
        }
        timer.start(timeoutTime(),this);
    }
}

void doubleSnakeBoard::paintEvent(QPaintEvent *paint)
{
    paintMessage(paint);
    if(command!=HELP&&state==RUN)
    {
        QPainter p;
        p.begin(this);
        QFont font("宋体",15,QFont::Bold,true);
        p.setFont(font);
        p.setPen(Qt::green);
        QRect rect=contentsRect();
        int boardTop = rect.top();
        int boardLeft=rect.left();
        snake1.Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        snake2.Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        p.end();
    }

}
