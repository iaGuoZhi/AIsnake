#define QT_NO_OPENGL
#include "doublesnakeboard.h"
#include "QDebug"
#include <QKeyEvent>

doubleSnakeBoard::doubleSnakeBoard(THEME theme,DIFFICULTY difficulty,QWidget *parent)
    : snakeboard(parent)
{
    this->theme=theme;
    this->difficulty=difficulty;
    timer.start(timeoutTime(),this);
}

void doubleSnakeBoard::start()
{
    score1=0;
    score2=0;
    level1=0;
    level2=0;
    remainhidetimes1=0;
    remainhidetimes2=0;
    hideleft1=0;
    hideleft2=0;
    environ=new environment(theme,difficulty);
    environ->initEnvironment();
    snake1=new Snake(SNAKEHEADX+5,SNAKEHEADY+3,5,DIRECTION::RIGHT,theme,"玩家一");
    snake2=new Snake(SNAKEHEADX-5,SNAKEHEADY-3,6,DIRECTION::LEFT,theme,"玩家二");
    snake1->initSnake();
    snake2->initSnake();
    emit score1Changed(score1);
    emit level1Changed(level1);
    emit score2Changed(score2);
    emit level2Changed(level2);
    emit hidetimes1Changed(remainhidetimes1);
    emit hidetimes2Changed(remainhidetimes2);
    state=RUN;
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
        snake1->QSchangeDirection(LEFT);
        break;
    case Qt::Key_Right:
        snake1->QSchangeDirection(RIGHT);
        break;
    case Qt::Key_Down:
        snake1->QSchangeDirection(DOWN);
        break;
    case Qt::Key_Up:
        snake1->QSchangeDirection(UP);
        break;
    case Qt::Key_Shift:
        if(remainhidetimes1>0&&hideleft1==0)
        {
            hideleft1+=HIDELENGTH;
            remainhidetimes1-=1;
            emit hidetimes1Changed(remainhidetimes1);
        }
        break;
    case Qt::Key_A:
        snake2->QSchangeDirection(LEFT);
        break;
    case Qt::Key_D:
        snake2->QSchangeDirection(RIGHT);
        break;
    case Qt::Key_S:
        snake2->QSchangeDirection(DOWN);
        break;
    case Qt::Key_W:
        snake2->QSchangeDirection(UP);
        break;
    case Qt::Key_Q:
        if(remainhidetimes2>0&&hideleft2==0)
        {
            hideleft2+=HIDELENGTH;
            remainhidetimes2-=1;
             emit hidetimes2Changed(remainhidetimes2);
        }
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void doubleSnakeBoard::timerEvent(QTimerEvent *event)
{
    int eatresult1=0,eatresult2=0;
    int capturesize1=-1,capturesize2=-1;

    if(event->timerId()==timer.timerId()){
        if(state==RUN&&command!=HELP)
        {
            /*implement hide func*/
            if(this->hideleft1>0)
            {
                snake1->hide();
                this->hideleft1-=1;
            }
            if(this->hideleft2>0)
            {
                snake2->hide();
                this->hideleft2-=1;
            }

            snake1->openChangeLock();
            snake2->openChangeLock();
            /*move snake*/
            snake1->QSmove();
            snake2->QSmove();

            /*snake eat food*/
            /*convert value to a variable,as QSeat() is not a constant func*/
            eatresult1=snake1->QSeat(environ->QVfood);
            eatresult2=snake2->QSeat(environ->QVfood);

            if(eatresult1!=-1)
            {
                score1+=3;
                level1=score1/7;
                snake1->QSgrow();
                emit score1Changed(score1);
                emit level1Changed(level1);

                if(environ->isHideBuff(eatresult1))
                {
                    this->remainhidetimes1+=1;
                    emit hidetimes1Changed(this->remainhidetimes1);

                }
                environ->createFood(eatresult1);
            }

            if(eatresult2!=-1)
            {
                score2+=3;
                level2=score2/7;
                snake2->QSgrow();
                emit score2Changed(score2);
                emit level2Changed(level2);
                if(environ->isHideBuff(eatresult2))
                {
                    this->remainhidetimes2+=1;
                    emit hidetimes2Changed(this->remainhidetimes2);

                }
                environ->createFood(eatresult2);
            }

            /*snake caputure snake*/
            capturesize1=snake1->capture(snake2->QVsnake);
            capturesize2=snake2->capture(snake1->QVsnake);

            if(capturesize1!=-1)
            {
                if(capturesize1==0)
                    state=END;

                score1+=3*capturesize1;
                level1=score1/7;
                emit score1Changed(score1);
                emit level1Changed(level1);
                score2-=3*capturesize1;
                level2=score2/7;
                emit score2Changed(score2);
                emit level2Changed(level2);

                snake1->QSquickGrow(capturesize1);
                snake2->QSquickShort(capturesize1);
            }else
            if(capturesize2!=-1)
            {
                if(capturesize2==0)
                    state=END;

                score2+=3*capturesize2;
                level2=score2/7;
                emit score2Changed(score2);
                emit level2Changed(level2);
                score1-=3*capturesize2;
                level1=score1/7;
                emit score1Changed(score1);
                emit level1Changed(level1);

                snake1->QSquickShort(capturesize2);
                snake2->QSquickGrow(capturesize2);
            }


            /*judge snake alive*/
            if(!snake1->QSalive(environ->QVbrick)||!snake2->QSalive(environ->QVbrick))
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
        environ->Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        snake1->Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        snake2->Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        p.end();
    }

}
