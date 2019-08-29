#define QT_NO_OPENGL
#include "watchaisnakeboard.h"
#include "QDebug"
#include <QKeyEvent>
watchAISnakeBoard::watchAISnakeBoard(QWidget *parent):snakeboard(parent)
{
    init();
    score=0;
    level=0;
    timer.start(timeoutTime(),this);
}

void watchAISnakeBoard::start()
{
    score=0;
    level=0;
    state=RUN;
    environ.initEnvironment();
    aisnake=new aiSnake(SNAKEHEADX,SNAKEHEADY,1,DIRECTION::RIGHT);
    aisnake->initSnake();

    emit scoreChanged(score);
    emit levelChanged(level);

}

void watchAISnakeBoard::timerEvent(QTimerEvent *event)
{
    int eatResult;
    if(event->timerId()==timer.timerId()){

        if(state==RUN&&command!=HELP)
        {
            eatResult=aisnake->QSeat(environ.QVfood);

            if(eatResult!=-1)
            {
                score+=3;
                level=score/3;
                aisnake->QSgrow();
                emit scoreChanged(score);
                emit levelChanged(level);

                environ.createFood(eatResult);
                 qDebug()<<aisnake->QVsnake.size();
            }

             aisnake->QSbfs(environ.QVfood,environ.QVbrick);
             aisnake->QSmove();

            if(!aisnake->QSalive(environ.QVbrick))
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


void watchAISnakeBoard::paintEvent(QPaintEvent *paint)
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
        int boardTop =rect.top();
        int boardLeft=rect.left();
        environ.Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        aisnake->Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        p.end();
    }

}
