#define QT_NO_OPENGL
#include "singlesnakeboard.h"
#include "QDebug"
#include <QKeyEvent>

singlesnakeboard::singlesnakeboard(QWidget *parent)
    : snakeboard(parent)
{
    init();
    score1=0;
    level1=0;
    remainhidetimes=0;
    hideleft=0;
    timer.start(timeoutTime(), this);
}

void singlesnakeboard::start()
{
    qDebug()<<"arrive start";
    state=RUN;
    snake.initSnake();

    emit score1Changed(score1);
    emit level1Changed(level1);
}

void singlesnakeboard::keyPressEvent(QKeyEvent *event)
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
        case Qt::Key_Shift:
            if(remainhidetimes>0)
            {
                qDebug()<<"key is right";
                hideleft+=HIDELENGTH;
                remainhidetimes-=1;
            }
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void singlesnakeboard::timerEvent(QTimerEvent *event)
{
    int eatResult;
    if(event->timerId()==timer.timerId()){
        if(state==RUN&&command!=HELP)
        {
            if(this->hideleft>0)
            {
                qDebug()<<"arrive hide";
                snake.hide();
                this->hideleft-=1;
            }
            snake.QSmove();
            eatResult=snake.QSeat();
            if(eatResult>0)
            {
                score1+=3;
                level1=score1/10;
                snake.QSgrow();
                emit score1Changed(score1);
                emit level1Changed(level1);

                if(eatResult==2)
                {
                    this->remainhidetimes+=1;
                    qDebug()<<this->remainhidetimes;
                    emit hidetimesChanged(this->remainhidetimes);
                }
            }
            if(!snake.QSalive())
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

void singlesnakeboard::paintEvent(QPaintEvent *paint)
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
        snake.Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        p.end();
    }

}
