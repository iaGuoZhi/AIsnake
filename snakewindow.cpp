#define QT_NO_OPENGL
#include <QtWidgets>
#include "snakewindow.h"
#include "snakeborder.h"

SnakeWindow::SnakeWindow()
{
    board=new SnakeBorder;

    scoreLcd=new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd=new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, board, &SnakeBorder::start);
    connect(quitButton , &QPushButton::clicked, qApp, &QApplication::quit);
    connect(pauseButton, &QPushButton::clicked, board, &SnakeBorder::pause);

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
    layout->addWidget(createLabel(tr("QSnake")),0,0);
    layout->addWidget(createLabel(tr("LEVEL")), 1, 0);
    layout->addWidget(levelLcd, 2, 0);
    layout->addWidget(createLabel(tr("SCORE")), 3, 0);
    layout->addWidget(scoreLcd, 4, 0);
    layout->addWidget(board, 0, 1, 5, 5);
    layout->addWidget(startButton, 5, 0);
    layout->addWidget(quitButton, 5, 2);
    layout->addWidget(pauseButton, 5, 4);
    board->setFocusPolicy(Qt::StrongFocus);


    setLayout(layout);
    setWindowTitle(tr("QSnake"));
    resize(550,370);
}

QLabel *SnakeWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
