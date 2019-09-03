#define QT_NO_OPENGL
#include"againstaiboard.h"
#include <QDebug>
#include <QKeyEvent>


againstAIBoard::againstAIBoard(THEME theme,DIFFICULTY difficulty,QWidget *parent)
    :snakeboard(parent)
{
    this->theme=theme;
    this->difficulty=difficulty;
    timer.start(timeoutTime(),this);
}

void againstAIBoard::start()
{
    score1=0;
    score2=0;
    level1=0;
    level2=0;

    environ=new environment(theme,difficulty);
    environ->initEnvironment();
    snake1=new Snake(SNAKEHEADX+5,SNAKEHEADY+3,5,DIRECTION::RIGHT,theme);
    aisnake2=new aiSnake(SNAKEHEADX-5,SNAKEHEADY-3,6,DIRECTION::LEFT,theme);
    snake1->initSnake();
    aisnake2->initSnake();
    emit score1Changed(score1);
    emit level1Changed(level1);
    emit score2Changed(score2);
    emit level2Changed(level2);

    state=RUN;
}


void againstAIBoard::keyPressEvent(QKeyEvent *event)
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
    default:
        QFrame::keyPressEvent(event);
    }
}

void againstAIBoard::timerEvent(QTimerEvent *event)
{
    int eatresult1=0,eatresult2=0;


    if(event->timerId()==timer.timerId()){
        if(state==RUN&&command!=HELP)
        {

            /*snake eat food*/
            /*convert value to a variable,as QSeat() is not a constant func*/
            eatresult1=snake1->QSeat(environ->QVfood);
            eatresult2=aisnake2->QSeat(environ->QVfood);

            if(eatresult1!=-1)
            {
                score1+=3;
                level1=score1/7;
                snake1->QSgrow();
                emit score1Changed(score1);
                emit level1Changed(level1);

                environ->createFood(eatresult1);
            }

            if(eatresult2!=-1)
            {
                score2+=3;
                level2=score2/7;
                aisnake2->QSgrow();
                emit score2Changed(score2);
                emit level2Changed(level2);

                environ->createFood(eatresult2);
            }

            /*move snake*/
            snake1->openChangeLock();
            snake1->QSmove();
            aisnake2->QSbfs(environ->QVfood,environ->QVbrick);
            aisnake2->QSmove();

            /*judge snake alive*/
            if(!snake1->QSalive(environ->QVbrick)||!aisnake2->QSalive(environ->QVbrick))
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



void againstAIBoard::paintEvent(QPaintEvent *paint)
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
        aisnake2->Qshow(p,squareWidth(),squareHeight(),boardLeft,boardTop);
        p.end();
    }

}
