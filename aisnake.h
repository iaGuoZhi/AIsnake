#define QT_NO_OPENGL
#ifndef AISNAKE_H
#define AISNAKE_H

#include"snake.h"
#include<vector>
using namespace std;

struct POINT{
    /*site of point*/
    int point_x;
    int point_y;
    /*is visited*/
    bool visit;
    /*the direction when bfs arrive the point*/
    DIRECTION arriveDirection;
    /*snake can move to the point or not*/
    bool safety;
    bool isfood;


};
class aiSnake:public Snake
{

   public:
    aiSnake(int sheadx,int sheady,int scolor,DIRECTION sdirection,THEME theme,QString name="");
    bool QSbfs(QVector<Unit> virtualSnake,QVector<Unit> virtualFood,QVector<Unit> virtualBrick);
    DIRECTION findDirection(QVector<Unit> virtualSnake,vector<vector<POINT>> table,POINT point);
    bool followTail(QVector<Unit> virtualSnake,QVector<Unit> virtualBrick);
    bool QSbfsPlus(QVector<Unit> virtualFood,QVector<Unit> virtualBrick);
    QVector<Unit> QSgenerateVirtualSnake(vector<vector<POINT>> table,POINT point,int size);
};

#endif // AISNAKE_H
