#define QT_NO_OPENGL
#include <QtWidgets>
#include "snakewindow.h"
#include "snakeboard.h"
#include<QDebug>

SnakeWindow::SnakeWindow()
{
    board=new snakeboard;
    scoreLcd1=new QLCDNumber(5);
    scoreLcd1->setSegmentStyle(QLCDNumber::Filled);
    levelLcd1=new QLCDNumber(5);
    levelLcd1->setSegmentStyle(QLCDNumber::Filled);

    scoreLcd2=new QLCDNumber(5);
    scoreLcd2->setSegmentStyle(QLCDNumber::Filled);
    levelLcd2=new QLCDNumber(5);
    levelLcd2->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    helpButton=new QPushButton(tr("&Help"));
    helpButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, board, &snakeboard::start);
    connect(quitButton , &QPushButton::clicked, this, &SnakeWindow::quit);
    connect(pauseButton, &QPushButton::clicked, board, &snakeboard::pause);
    connect(helpButton,&QPushButton::clicked,board,&snakeboard::help);

#if __cplusplus >= 201402L
    connect(board, &SnakeBoard::scoreChanged,
            scoreLcd1, qOverload<int>(&QLCDNumber::display));
    connect(board, &SnakeBoard::levelChanged,
            levelLcd1, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &snakeboard::scoreChanged,
            scoreLcd1, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &snakeboard::levelChanged,
            levelLcd1, QOverload<int>::of(&QLCDNumber::display));

#endif
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

    /*draw game window according to game mode*/
    switch(this->mode)
    {
    case GAMEMODE::SINGLEPLAYER:  case GAMEMODE::WATCHAIPLAY:

        layout->addWidget(board, 0, 0,11,16);
        if(this->mode==SINGLEPLAYER)
        layout->addWidget(createLabel(tr("单人游戏")),0,16,1,2);
        else{
            layout->addWidget(createLabel(tr("AI贪吃蛇")),0,16,1,2);
        }
        layout->addWidget(createLabel(tr("等级")), 1, 16,1,2);
        layout->addWidget(levelLcd1, 2, 16,1,2);
        layout->addWidget(createLabel(tr("分数")), 3, 16,1,2);
        layout->addWidget(scoreLcd1, 4, 16,1,2);
        layout->addWidget(createLabel(tr("难度: ")+this->difficultyString),5,16,1,2);
        layout->addWidget(startButton, 6, 16,1,2);
        layout->addWidget(pauseButton, 7, 16,1,2);
        layout->addWidget(helpButton,8,16,1,2);
        layout->addWidget(quitButton, 9, 16,1,2);
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
        layout->addWidget(createLabel(tr("难度: ")+this->difficultyString),5,0,1,2);
        layout->addWidget(createLabel(tr("AWSD方向")),6,0,1,2);
        layout->addWidget(createLabel(tr("Q键隐身")),7,0,1,2);
        layout->addWidget(helpButton,8,0,2,2);
        layout->addWidget(pauseButton,10,0,2,2);

        /*游戏区*/
        layout->addWidget(board,0,2,12,16);

        /*右边信息区*/
        layout->addWidget(createLabel(tr("玩家一")),0,18,1,2);
        layout->addWidget(createLabel(tr("等级")),1,18,1,2);
        layout->addWidget(levelLcd1,2,18,1,2);
        layout->addWidget(createLabel(tr("分数")),3,18,1,2);
        layout->addWidget(scoreLcd1,4,18,1,2);
        layout->addWidget(createLabel(tr("难度: ")+this->difficultyString),5,18,1,2);
        layout->addWidget(createLabel(tr("方向键移动")),6,18,1,2);
        layout->addWidget(createLabel(tr("?键隐身")),7,18,1,2);
        layout->addWidget(startButton,8,18,2,2);
        layout->addWidget(quitButton,10,18,2,2);

        break;
    }
    layout->setMargin(0);
    setLayout(layout);

    setWindowTitle(tr("QSnake"));
    resize(700,450);
}
