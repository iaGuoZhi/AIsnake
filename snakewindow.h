#define QT_NO_OPENGL
#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H
#include <QFrame>
#include<QWidget>
#include<QString>

#include "snakeboard.h"
#include "shareinfo.h"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class snakeboard;

class SnakeWindow: public QWidget
{
    Q_OBJECT
public:
    SnakeWindow();
    ~SnakeWindow(){
        quit();
    }
    void quit();

signals:
    void backHomepage();
private:
    GAMEMODE mode;
    THEME theme;
    int difficulty;

    QString difficultyString;

    snakeboard *board;

    QLCDNumber *scoreLcd1;
    QLCDNumber *scoreLcd2;
    QLCDNumber *levelLcd1;
    QLCDNumber *levelLcd2;

    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
    QPushButton *helpButton;

    QLabel *createLabel(const QString &text);
public:

    void remakeAsOrder(GAMEMODE mode,THEME theme,int difficulty);
};

#endif // SNAKEWINDOW_H
