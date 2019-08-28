#define QT_NO_OPENGL
#ifndef DOUBLESNAKEBOARD_H
#define DOUBLESNAKEBOARD_H

#include "snakeboard.h"
#include "snake.h"


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

private:
    int score1,score2;
    int level1,level2;
    Snake snake1,snake2;
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
