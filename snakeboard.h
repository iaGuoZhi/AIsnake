#define QT_NO_OPENGL
#ifndef snakeboard_H
#define snakeboard_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include"snake.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

enum STATE{
    RUN,PAUSE,END,WAIT
};
enum COMMAND{
    HELP,EMPTY
};

const int HIDELENGTH=8;

class snakeboard : public QFrame
{
    Q_OBJECT

public:
    snakeboard(QWidget *parent=0);


public slots:
    void pause();
    void help();




protected:
    STATE state;
    COMMAND command;



    //void drawSnake();
   // void drawSquare(QPainter &painter, int x, int y, int shape);
    void init();
    int squareWidth() { return contentsRect().width() / BOARDWIDTH; }
    int squareHeight() { return contentsRect().height() / BOARDHEIGHT; }
    void paintMessage(QPaintEvent *);
    void playBackgroundMusic();
    void playEatingMusic();
    void playFaultMusic();


};

#endif // snakeboard_H
