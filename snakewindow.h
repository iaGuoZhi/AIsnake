#define QT_NO_OPENGL
#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H
#include <QFrame>
#include<QWidget>

#include "snakeborder.h"
#include "shareinfo.h"

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
    void quit();

signals:
    void backHomepage();
private:
    GAMEMODE mode;
    THEME theme;
    int difficulty;

    SnakeBorder *board;

    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
    QPushButton *helpButton;

    QLabel *createLabel(const QString &text);
public:

    void remakeAsOrder(GAMEMODE mode,THEME theme,int difficulty);
};

#endif // SNAKEWINDOW_H
