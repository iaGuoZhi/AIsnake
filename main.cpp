#define QT_NO_OPENGL
#include <QtWidgets>
#include <stdlib.h>
#include "snakewindow.h"
#include "homepage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*SnakeWindow window;
    window.show();*/
    Homepage homepage;
    homepage.resize(800,400);
    homepage.show();
    return a.exec();
}
/*
window.h
board.h
Snake.h
Unit.h
*/
