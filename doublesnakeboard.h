#define QT_NO_OPENGL
#ifndef DOUBLESNAKEBOARD_H
#define DOUBLESNAKEBOARD_H

#include "snakeboard.h"
#include "snake.h"
#include "shareinfo.h"
#include<QDebug>


#define MAX(x, y)   ((x)>(y)?(x):(y))
class doubleSnakeBoard:public snakeboard
{
    Q_OBJECT
public:
    doubleSnakeBoard(QWidget *parent=0);

public slots:
    void start();

signals:
    void score1Changed(int score1);
    void score2Changed(int score2);
    void level1Changed(int level1);
    void level2Changed(int level2);
    void hidetimes1Changed(int hidetimes);
    void hidetimes2Changed(int hidetimes);

private:
    int score1,score2;
    int level1=0,level2=0;
    Snake *snake1,*snake2;
    environment environ;
    int remainhidetimes1=0,remainhidetimes2=0;
    int hideleft1=0,hideleft2=0;

    QBasicTimer timer;

    int timeoutTime()
    {
        return 400/(1+MAX(level1,level2));
    }

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *) override;

};

#endif // DOUBLESNAKEBOARD_H
