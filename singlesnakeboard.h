#define QT_NO_OPENGL
#ifndef SINGLESNAKEBOARD_H
#define SINGLESNAKEBOARD_H

#include"snakeboard.h"
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include "snake.h"

class singlesnakeboard:public snakeboard
{
    Q_OBJECT

public:
    singlesnakeboard(QWidget *parent=0);

public slots:
    void start();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);

private:

    int level;
    int score;
    Snake snake;
    QBasicTimer timer;

    int timeoutTime()
    {
        return 400/(1+level);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *) override;

};

#endif // SINGLESNAKEBOARD_H
