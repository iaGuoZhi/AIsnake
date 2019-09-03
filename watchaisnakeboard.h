#define QT_NO_OPENGL
#ifndef WATCHAISNAKEBOARD_H
#define WATCHAISNAKEBOARD_H

#include "snakeboard.h"
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include "aisnake.h"
#include "environment.h"
#include "shareinfo.h"

class watchAISnakeBoard:public snakeboard
{
    Q_OBJECT
public:
    watchAISnakeBoard(THEME theme=THEME::COSTOM_FOREST,DIFFICULTY difficulty=DIFFICULTY::MEDIUM,QWidget *parent=0);

public slots:
    void start();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);

private:
    int level=0;
    int score=0;

    environment *environ;
    aiSnake *aisnake;

    THEME theme;
    DIFFICULTY difficulty;

    QBasicTimer timer;

    int timeoutTime(){
        return 15;
    }

protected:
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *) override;
};

#endif // WATCHAISNAKEBOARD_H
