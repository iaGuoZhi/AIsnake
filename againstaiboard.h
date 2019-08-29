#define QT_NO_OPENGL
#ifndef AGAINSTAIBOARD_H
#define AGAINSTAIBOARD_H

#include "snakeboard.h"
#include "snake.h"
#include "shareinfo.h"
#include "aisnake.h"
#include <QDebug>


#define MAX(x, y)   ((x)>(y)?(x):(y))

class againstAIBoard:public snakeboard
{
    Q_OBJECT
public:
    againstAIBoard(QWidget *parent=0);

public slots: void start();

signals:
    void score1Changed(int score1);
    void score2Changed(int score2);
    void level1Changed(int level1);
    void level2Changed(int level2);

private:
    int score1,score2;
    int level1=0,level2=0;
    Snake *snake1;
    aiSnake *aisnake2;
    environment environ;

    QBasicTimer timer;

    int timeoutTime(){
        return 2000/(7+MAX(level1,level2));
    }

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *) override;
};

#endif // AGAINSTAIBOARD_H
