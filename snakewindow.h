#define QT_NO_OPENGL
#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H
#include <QFrame>
#include<QWidget>
#include<QString>

#include "singlesnakeboard.h"
#include "doublesnakeboard.h"
#include "watchaisnakeboard.h"
#include "againstaiboard.h"
#include "shareinfo.h"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class singlesnakeboard;

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
    GAMEMODE mode=GAMEMODE::SINGLEPLAYER;
    THEME theme=THEME::COSTOM_FOREST;
    int difficulty=50;

    QString difficultyString;

    singlesnakeboard *singleboard;
    doubleSnakeBoard *doubleboard;
    watchAISnakeBoard *watchaiboard;
    againstAIBoard *againstaiboard;


    QLCDNumber *scoreLcd1;
    QLCDNumber *scoreLcd2;
    QLCDNumber *levelLcd1;
    QLCDNumber *levelLcd2;
    QLCDNumber *hideTimesLcd1;
    QLCDNumber *hideTimesLcd2;

    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
    QPushButton *helpButton;

    QLabel *createLabel(const QString &text);
    void reconnectAsOrder();
public:

    void remakeAsOrder(GAMEMODE mode,THEME theme,int difficulty);
};

#endif // SNAKEWINDOW_H
