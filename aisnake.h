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
    bool safefy;



};
class aiSnake:public Snake
{
   public:
    aiSnake(int sheadx,int sheady,int scolor,DIRECTION sdirection);
    bool QSbfs(QVector<Unit> virturlFood,QVector<Unit> virturlBrick);
    DIRECTION findDirection(vector<vector<POINT>> table,POINT point);
};

#endif // AISNAKE_H
