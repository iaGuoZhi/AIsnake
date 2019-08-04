#define QT_NO_OPENGL
#include "snakeborder.h"
#include <QtWidgets>
#include<QDebug>
SnakeBorder::SnakeBorder(QWidget *parent)
: QFrame(parent)
{

    setObjectName("myframe");
    setStyleSheet("QFrame#myframe{border-image:url(../qSnake/images/ditu.jpg)}" );
    setFocusPolicy(Qt::StrongFocus);
    level=0;
    state=WAIT;
    score=0;
}

void SnakeBorder::start()
{

    state=RUN;
    score=0;
    level=0;
    snake.initSnake();
    emit scoreChanged(score);
    emit levelChanged(level);
    timer.start(timeoutTime(), this);
}

void SnakeBorder::pause()
{
    state=PAUSE;
}
void SnakeBorder::keyPressEvent(QKeyEvent *event)
{
    if(state!=RUN)
    {
        QFrame::keyPressEvent(event);
        return;
    }
    switch (event->key()) {
        case Qt::Key_Left:
        snake.QSchangeDirection(LEFT);
            break;
        case Qt::Key_Right:
            snake.QSchangeDirection(RIGHT);
            break;
        case Qt::Key_Down:
            snake.QSchangeDirection(DOWN);
            break;
        case Qt::Key_Up:
            snake.QSchangeDirection(UP);
            break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void SnakeBorder::paintEvent(QPaintEvent *)
{
    QPainter p;
    p.begin(this);
     QRect rect=contentsRect();
    if(state==RUN){
      int boardTop = rect.bottom() - BOARDHEIGHT*squareHeight();
      int boardLeft=rect.left();
      snake.Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
    }
    if(state==WAIT)
    {
        p.drawText(20,20,"are you ready?");
    }
    if(state==END)
    {
        p.drawText(rect, Qt::AlignCenter, tr("END"));
    }
    if(state==PAUSE)
    {
        p.drawText(rect, Qt::AlignCenter, tr("Pause"));
    }
    p.end();
}

void SnakeBorder::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timer.timerId()){
        if(state==RUN)
        {
            snake.QSmove();
            if(snake.QSeat())
            {
                score+=3;
                level=score/10;
                snake.QSgrow();
                emit scoreChanged(score);
                emit levelChanged(level);
            }
            if(!snake.QSalive())
            {
                state=END;
            }
            update();
        }
        timer.start(timeoutTime(),this);
    }
}




