#define QT_NO_OPENGL
#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H
#include <QFrame>
#include<QWidget>

#include "snakeborder.h"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class SnakeBorder;

class SnakeWindow: public QWidget
{
    Q_OBJECT
public:
    SnakeWindow();

private:
    SnakeBorder *board;

    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;

    QLabel *createLabel(const QString &text);

};

#endif // SNAKEWINDOW_H
