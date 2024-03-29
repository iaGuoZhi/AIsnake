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
    againstAIBoard(THEME theme=THEME::COSTOM_FOREST,DIFFICULTY difficulty=DIFFICULTY::MEDIUM,QWidget *parent=0);

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
    environment *environ;

    THEME theme;
    DIFFICULTY difficulty;

    QBasicTimer timer;

    int timeoutTime(){
        return 10000/(24+MAX(level1,level2)*(difficulty+1)+2*difficulty);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *) override;
};

#endif // AGAINSTAIBOARD_H
