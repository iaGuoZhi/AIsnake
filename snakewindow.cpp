#define QT_NO_OPENGL
#include <QtWidgets>
#include "snakewindow.h"
#include "singlesnakeboard.h"
#include<QDebug>

SnakeWindow::SnakeWindow()
{
    scoreLcd1=new QLCDNumber(5);
    scoreLcd1->setSegmentStyle(QLCDNumber::Filled);
    levelLcd1=new QLCDNumber(5);
    levelLcd1->setSegmentStyle(QLCDNumber::Filled);

    scoreLcd2=new QLCDNumber(5);
    scoreLcd2->setSegmentStyle(QLCDNumber::Filled);
    levelLcd2=new QLCDNumber(5);
    levelLcd2->setSegmentStyle(QLCDNumber::Filled);

    hideTimesLcd1=new QLCDNumber(5);
    hideTimesLcd1->setSegmentStyle(QLCDNumber::Filled);
    hideTimesLcd2=new QLCDNumber(5);
    hideTimesLcd2->setSegmentStyle(QLCDNumber::Filled);



    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    helpButton=new QPushButton(tr("&Help"));
    helpButton->setFocusPolicy(Qt::NoFocus);
}

void SnakeWindow::reconnectAsOrder()
{
    switch (this->mode) {
    case GAMEMODE::WATCHAIPLAY:
        watchaiboard=new watchAISnakeBoard();

        connect(startButton, &QPushButton::clicked, watchaiboard, &watchAISnakeBoard::start);
        connect(quitButton , &QPushButton::clicked, this, &SnakeWindow::quit);
        connect(pauseButton, &QPushButton::clicked, watchaiboard, &watchAISnakeBoard::pause);
        connect(helpButton,&QPushButton::clicked,watchaiboard,&watchAISnakeBoard::help);

        connect(watchaiboard, &watchAISnakeBoard::scoreChanged,
                scoreLcd1, QOverload<int>::of(&QLCDNumber::display));
        connect(watchaiboard, &watchAISnakeBoard::levelChanged,
                levelLcd1, QOverload<int>::of(&QLCDNumber::display));
        break;

    case GAMEMODE::SINGLEPLAYER:
        singleboard=new singlesnakeboard();

        connect(startButton, &QPushButton::clicked, singleboard, &singlesnakeboard::start);
        connect(quitButton , &QPushButton::clicked, this, &SnakeWindow::quit);
        connect(pauseButton, &QPushButton::clicked, singleboard, &singlesnakeboard::pause);
        connect(helpButton,&QPushButton::clicked,singleboard,&singlesnakeboard::help);

        connect(singleboard, &singlesnakeboard::score1Changed,
                scoreLcd1, QOverload<int>::of(&QLCDNumber::display));
        connect(singleboard, &singlesnakeboard::level1Changed,
                levelLcd1, QOverload<int>::of(&QLCDNumber::display));
        connect(singleboard,&singlesnakeboard::hidetimesChanged,
                hideTimesLcd1,QOverload<int>::of(&QLCDNumber::display));

        break;
    case GAMEMODE::DOUBLEPLAYER:
        doubleboard=new doubleSnakeBoard();

        connect(startButton, &QPushButton::clicked, doubleboard, &doubleSnakeBoard::start);
        connect(quitButton , &QPushButton::clicked, this, &SnakeWindow::quit);
        connect(pauseButton, &QPushButton::clicked, doubleboard, &doubleSnakeBoard::pause);
        connect(helpButton,&QPushButton::clicked,doubleboard,&doubleSnakeBoard::help);

        connect(doubleboard, &doubleSnakeBoard::score1Changed,
                scoreLcd1, QOverload<int>::of(&QLCDNumber::display));
        connect(doubleboard, &doubleSnakeBoard::level1Changed,
                levelLcd1, QOverload<int>::of(&QLCDNumber::display));
        connect(doubleboard, &doubleSnakeBoard::score2Changed,
                scoreLcd2, QOverload<int>::of(&QLCDNumber::display));
        connect(doubleboard, &doubleSnakeBoard::level2Changed,
                levelLcd2, QOverload<int>::of(&QLCDNumber::display));
        connect(doubleboard,&doubleSnakeBoard::hidetimes1Changed,
                hideTimesLcd1,QOverload<int>::of(&QLCDNumber::display));
        connect(doubleboard,&doubleSnakeBoard::hidetimes2Changed,
                hideTimesLcd2,QOverload<int>::of(&QLCDNumber::display));


    default:
        break;
    }
}
QLabel *SnakeWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}

void SnakeWindow::quit()
{

   this->hide();
   emit backHomepage();
}

void SnakeWindow::remakeAsOrder(GAMEMODE mode, THEME theme, int difficulty)
{
    /*receive data from homepage*/
    this->mode=mode;
    this->theme=theme;
    this->difficulty=difficulty;
    switch (this->difficulty) {
    case 0:
        this->difficultyString="非常简单";
        break;
    case 1:
        this->difficultyString="简单";
        break;
    case 2:
        this->difficultyString="中等";
        break;
    case 3:
        this->difficultyString="困难";
        break;
    case 4:
        this->difficultyString="非常困难";
        break;
    default:
        break;
    }

    QGridLayout *layout=new QGridLayout;

    /*reconnect signal and slot acoording to mode*/
    reconnectAsOrder();

    /*draw game window according to game mode*/
    switch(this->mode)
    {
    case GAMEMODE::SINGLEPLAYER:

        layout->addWidget(singleboard, 0, 0,13,18);

        layout->addWidget(createLabel(tr("单人游戏")),0,18,1,2);
        layout->addWidget(createLabel(tr("等级")), 1, 18,1,2);
        layout->addWidget(levelLcd1, 2, 18,1,2);
        layout->addWidget(createLabel(tr("分数")), 3, 18,1,2);
        layout->addWidget(scoreLcd1, 4, 18,1,2);
        layout->addWidget(createLabel(tr("剩余隐身数")),5,18,1,2);
        layout->addWidget(hideTimesLcd1,6,18,1,2);
        layout->addWidget(createLabel(tr("难度: ")+this->difficultyString),7,18,1,2);

        layout->addWidget(startButton, 8, 18,2,2);
        layout->addWidget(pauseButton, 10, 18,1,2);
        layout->addWidget(helpButton,11,18,1,2);
        layout->addWidget(quitButton, 12, 18,1,2);
        break;
     case GAMEMODE::WATCHAIPLAY:
        layout->addWidget(watchaiboard, 0, 0,13,18);

        layout->addWidget(createLabel(tr("AI贪吃蛇")),0,18,1,2);
        layout->addWidget(createLabel(tr("等级")), 1, 18,1,2);
        layout->addWidget(levelLcd1, 2, 18,1,2);
        layout->addWidget(createLabel(tr("分数")), 3, 18,1,2);
        layout->addWidget(scoreLcd1, 4, 18,1,2);
        layout->addWidget(createLabel(tr("难度: ")+this->difficultyString),7,18,1,2);

        layout->addWidget(startButton, 8, 18,2,2);
        layout->addWidget(pauseButton, 10, 18,1,2);
        layout->addWidget(helpButton,11,18,1,2);
        layout->addWidget(quitButton, 12, 18,1,2);
        break;

    case GAMEMODE::DOUBLEPLAYER: case GAMEMODE::PLAYWITHAI:
        /*左边信息区*/
        if(this->mode==DOUBLEPLAYER)
        layout->addWidget(createLabel(tr("玩家二")),0,0,1,2);
        else{
            layout->addWidget(createLabel(tr("AI玩家")),0,0,1,2);
        }
        layout->addWidget(createLabel(tr("等级")),1,0,1,2);
        layout->addWidget(levelLcd2,2,0,1,2);
        layout->addWidget(createLabel(tr("分数")),3,0,1,2);
        layout->addWidget(scoreLcd2,4,0,1,2);
        layout->addWidget(createLabel(tr("剩余隐身数")),5,0,1,2);
        layout->addWidget(hideTimesLcd2,6,0,1,2);
        layout->addWidget(createLabel(tr("难度: ")+this->difficultyString),7,0,1,2);
        layout->addWidget(createLabel(tr("AWSD方向")),8,0,1,2);
        layout->addWidget(createLabel(tr("Q键隐身")),9,0,1,2);
        layout->addWidget(helpButton,10,0,2,2);
        layout->addWidget(pauseButton,12,0,2,2);

        /*游戏区*/
        layout->addWidget(doubleboard,0,2,14,24);

        /*右边信息区*/
        layout->addWidget(createLabel(tr("玩家一")),0,26,1,2);
        layout->addWidget(createLabel(tr("等级")),1,26,1,2);
        layout->addWidget(levelLcd1,2,26,1,2);
        layout->addWidget(createLabel(tr("分数")),3,26,1,2);
        layout->addWidget(scoreLcd1,4,26,1,2);
        layout->addWidget(createLabel(tr("剩余隐身数")),5,26,1,2);
        layout->addWidget(hideTimesLcd1,6,26,1,2);
        layout->addWidget(createLabel(tr("难度: ")+this->difficultyString),7,26,1,2);
        layout->addWidget(createLabel(tr("方向键移动")),8,26,1,2);
        layout->addWidget(createLabel(tr("?键隐身")),9,26,1,2);
        layout->addWidget(startButton,10,26,2,2);
        layout->addWidget(quitButton,12,26,2,2);

        break;
    }
    layout->setMargin(0);
    setLayout(layout);

    setWindowTitle(tr("QSnake"));
    resize(1000,600);
}
