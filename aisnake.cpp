#include "aisnake.h"
#include<QQueue>
#include<vector>
using namespace std;

aiSnake::aiSnake(int sheadx,int sheady,int scolor,DIRECTION sdirection):Snake(sheadx,sheady,scolor,sdirection)
{

}

bool aiSnake::QSbfs(QVector<Unit> virtualFood, QVector<Unit> virtualBrick)
{
    vector<vector<POINT>> table(BOARDHEIGHT,vector<POINT>(BOARDWIDTH));
    /*the queue in bfs*/
    QQueue<POINT> path;
    POINT point,adjacentPoint;
    DIRECTION direction;

    for(int i=0;i<BOARDHEIGHT;++i)
    {
        for(int j=0;j<BOARDWIDTH;++j)
        {
            table.at(i).at(j).point_y=i;
            table.at(i).at(j).point_x=j;
            table.at(i).at(j).visit=false;
            table.at(i).at(j).safefy=true;
            table.at(i).at(j).arriveDirection=NONE;

            /*judge unsafe quickly*/
            if(i==0||j==0||i==BOARDHEIGHT-1||j==BOARDWIDTH-1)
            {
                table.at(i).at(j).safefy=false;
            }
            else{
                for(int k=0;k<virtualBrick.size();++k)
                {
                    if(i==virtualBrick[k].getUnitY()&&j==virtualBrick[k].getUnitX())
                        table.at(i).at(j).safefy=false;
                }
                for(int k=0;k<QVsnake.size();++k)
                {
                    if(i==QVsnake[k].getUnitY()&&j==QVsnake[k].getUnitX())
                    {
                        table.at(i).at(j).safefy=false;
                    }
                }
            }
        }
    }

    /*snake head enqueue*/
    table.at(QVsnake[0].getUnitY()).at(QVsnake[0].getUnitX()).visit=true;
    path.enqueue(table.at(QVsnake[0].getUnitY()).at(QVsnake[0].getUnitX()));


    while(!path.isEmpty())
    {
        point=path.dequeue();

        /*judge the dequeued point is food or not*/
        for(int i=0;i<virtualFood.size();++i)
        {
            if(virtualFood[i].getUnitY()==point.point_y&&virtualFood[i].getUnitX()==point.point_x)
            {
                direction=findDirection(table,point);
                QSchangeDirection(direction);
                return true;   //the ideal direction exists
            }
        }

        /*the left point enqueue*/
        adjacentPoint=table.at(point.point_y).at(point.point_x-1);
        if(adjacentPoint.safefy==true&&adjacentPoint.visit==false)
        {
            adjacentPoint.visit=true;
            adjacentPoint.arriveDirection=LEFT;
            path.enqueue(adjacentPoint);
        }
        /*the right point enqueue*/
        adjacentPoint=table.at(point.point_y).at(point.point_x+1);
        if(adjacentPoint.safefy==true&&adjacentPoint.visit==false)
        {
            adjacentPoint.visit=true;
            adjacentPoint.arriveDirection=RIGHT;
            path.enqueue(adjacentPoint);
        }
        /*the above point enqueue*/
        adjacentPoint=table.at(point.point_y-1).at(point.point_x);
        if(adjacentPoint.safefy==true&&adjacentPoint.visit==false)
        {
            adjacentPoint.visit=true;
             adjacentPoint.arriveDirection=UP;
            path.enqueue(adjacentPoint);
        }
        /*the down point enqueue*/
        adjacentPoint=table.at(point.point_y+1).at(point.point_x);
        if(adjacentPoint.safefy==true&&adjacentPoint.visit==false)
        {
            adjacentPoint.visit=true;
             adjacentPoint.arriveDirection=DOWN;
            path.enqueue(adjacentPoint);
        }

    }
    /* not find suitable direction*/
    return false;
}

 DIRECTION aiSnake::findDirection(vector<vector<POINT>> table,POINT point)
 {
     POINT backPoint,backPoint2;
     backPoint=point;
     while(!(backPoint.point_x==QVsnake[0].getUnitX()&&backPoint.point_y==QVsnake[0].getUnitY())){
         if(backPoint.arriveDirection==NONE)
         {
            return NONE;
         }
         backPoint2=backPoint;
         switch (backPoint.arriveDirection) {
         case LEFT:
             backPoint=table.at(backPoint.point_y).at(backPoint.point_x+1);
             break;
         case RIGHT:
              backPoint=table.at(backPoint.point_y).at(backPoint.point_x-1);
             break;
         case UP:
             backPoint=table.at(backPoint.point_y).at(backPoint.point_x+1);
             break;
         case DOWN:
              backPoint=table.at(backPoint.point_y).at(backPoint.point_x-1);
             break;
         default:
             break;
         }
     }
     return backPoint2.arriveDirection;
 }
