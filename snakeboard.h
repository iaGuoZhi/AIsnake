#define QT_NO_OPENGL
#ifndef snakeboard_H
#define snakeboard_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>

#include "snake.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class snakeboard : public QFrame
{
    Q_OBJECT
    enum STATE{
        RUN,PAUSE,END,WAIT
    };
    enum COMMAND{
        HELP,EMPTY
    };

public:
    snakeboard(QWidget *parent=0);


public slots:
    void start();
    void pause();
    void help();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);


private:

    int level;
    int score;
    STATE state;
    COMMAND command;
    Snake snake;
    QBasicTimer timer;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
     void paintEvent(QPaintEvent *) override;
private:
    void drawSnake();
    void drawSquare(QPainter &painter, int x, int y, int shape);
    int squareWidth() { return contentsRect().width() / BOARDWIDTH; }
    int squareHeight() { return contentsRect().height() / BOARDHEIGHT; }
    int timeoutTime()
    {
        return 400/(1+level);
    }
};

#endif // snakeboard_H
