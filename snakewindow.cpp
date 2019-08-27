#define QT_NO_OPENGL
#include <QtWidgets>
#include "snakewindow.h"
#include "snakeborder.h"
#include<QDebug>

SnakeWindow::SnakeWindow()
{
    board=new SnakeBorder;
    scoreLcd=new QLCDNumber(5);   //specify the max length of the number
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    //scoreLcd->setStyleSheet("border-image:url(../qSnake/images/ditu.jpg)" );
    levelLcd=new QLCDNumber(5);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    helpButton=new QPushButton(tr("&Help"));
    helpButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, board, &SnakeBorder::start);
    connect(quitButton , &QPushButton::clicked, this, &SnakeWindow::quit);
    connect(pauseButton, &QPushButton::clicked, board, &SnakeBorder::pause);
    connect(helpButton,&QPushButton::clicked,board,&SnakeBorder::help);

#if __cplusplus >= 201402L
    connect(board, &SnakeBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &SnakeBoard::levelChanged,
            levelLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &SnakeBorder::scoreChanged,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &SnakeBorder::levelChanged,
            levelLcd, QOverload<int>::of(&QLCDNumber::display));

#endif

    QGridLayout *layout=new QGridLayout;
    //layout->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    layout->addWidget(createLabel(tr("一号玩家")),0,0,1,1);
    layout->addWidget(createLabel(tr("LEVEL")), 1, 0,1,1);
    layout->addWidget(levelLcd, 2, 0,1,1);
    layout->addWidget(createLabel(tr("SCORE")), 3, 0,1,1);
    layout->addWidget(scoreLcd, 4, 0,1,1);
    layout->addWidget(pauseButton, 5, 0,1,1);
    layout->addWidget(helpButton,6,0,1,1);

    layout->addWidget(board, 0, 1,9,9);

    layout->addWidget(createLabel(tr("二号玩家")),0,10,1,1);
    layout->addWidget(createLabel(tr("LEVEL")), 1, 10,1,1);
    layout->addWidget(levelLcd, 2, 10,1,1);
    layout->addWidget(createLabel(tr("SCORE")), 3, 10,1,1);
    layout->addWidget(scoreLcd, 4, 10,1,1);

    layout->addWidget(startButton, 5, 10,1,1);
    layout->addWidget(quitButton, 6, 10,1,1);
    layout->setMargin(0);

    setLayout(layout);
    setWindowTitle(tr("QSnake"));
    resize(700,450);
}

QLabel *SnakeWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}

void SnakeWindow::quit()
{
   qDebug()<<this->mode;
   emit backHomepage();
}

void SnakeWindow::remakeAsOrder(GAMEMODE mode, THEME theme, int difficulty)
{
    this->mode=mode;
    this->theme=theme;
    this->difficulty=difficulty;
    qDebug()<<this->difficulty;
}
