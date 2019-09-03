#include "aisnake.h"
#include<QQueue>
#include<vector>
#include<QDebug>
using namespace std;

aiSnake::aiSnake(int sheadx,int sheady,int scolor,DIRECTION sdirection,THEME theme,QString name):Snake(sheadx,sheady,scolor,sdirection,theme,name)
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
            table.at(i).at(j).safety=true;
            table.at(i).at(j).arriveDirection=NONE;
            table.at(i).at(j).isfood=false;
        }
    }

    for(int k=0;k<virtualBrick.size();++k)
    {
        table.at(virtualBrick[k].getUnitY()).at(virtualBrick[k].getUnitX()).safety=false;
    }
    for(int k=0;k<QVsnake.size();++k)
    {
        table.at(QVsnake[k].getUnitY()).at(QVsnake[k].getUnitX()).safety=false;
    }

    /*judge food is in the point or not*/
    for(int k=0;k<virtualFood.size();++k)
    {
        table.at(virtualFood[k].getUnitY()).at(virtualFood[k].getUnitX()).isfood=true;
    }

    /*snake head enqueue*/
    table.at(QVsnake[0].getUnitY()).at(QVsnake[0].getUnitX()).visit=true;
    path.enqueue(table.at(QVsnake[0].getUnitY()).at(QVsnake[0].getUnitX()));



    while(!path.isEmpty())
    {
        point=path.dequeue();

        if(point.isfood==true){
                direction=findDirection(table,point);
                openChangeLock();
                if(direction==NONE)
                    return false;
                QSchangeDirection(direction);
                return true;   //the ideal direction exists
        }

        /*the left point enqueue*/
        adjacentPoint=table.at(point.point_y).at(point.point_x-1);
        if(adjacentPoint.safety==true&&adjacentPoint.visit==false)
        {
            table.at(point.point_y).at(point.point_x-1).visit=true;
            table.at(point.point_y).at(point.point_x-1).arriveDirection=LEFT;
            path.enqueue(adjacentPoint);
        }
        /*the right point enqueue*/
        adjacentPoint=table.at(point.point_y).at(point.point_x+1);
        if(adjacentPoint.safety==true&&adjacentPoint.visit==false)
        {
            table.at(point.point_y).at(point.point_x+1).visit=true;
           table.at(point.point_y).at(point.point_x+1).arriveDirection=RIGHT;
            path.enqueue(adjacentPoint);
        }
        /*the above point enqueue*/
        adjacentPoint=table.at(point.point_y-1).at(point.point_x);
        if(adjacentPoint.safety==true&&adjacentPoint.visit==false)
        {
            table.at(point.point_y-1).at(point.point_x).visit=true;
            table.at(point.point_y-1).at(point.point_x).arriveDirection=UP;
            path.enqueue(adjacentPoint);
        }
        /*the down point enqueue*/
        adjacentPoint=table.at(point.point_y+1).at(point.point_x);
        if(adjacentPoint.safety==true&&adjacentPoint.visit==false)
        {
            table.at(point.point_y+1).at(point.point_x).visit=true;
            table.at(point.point_y+1).at(point.point_x).arriveDirection=DOWN;
            path.enqueue(adjacentPoint);
        }

    }
    /* not find suitable direction*/
    return false;
}

 DIRECTION aiSnake::findDirection(vector<vector<POINT>> table,POINT point)
 {

     POINT backPoint,backPoint2;
     backPoint=table.at(point.point_y).at(point.point_x);
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
             backPoint=table.at(backPoint.point_y+1).at(backPoint.point_x);
             break;
         case DOWN:
              backPoint=table.at(backPoint.point_y-1).at(backPoint.point_x);
             break;
         default:
             break;
         }
     }

     return backPoint2.arriveDirection;
 }

 bool aiSnake::followTail(QVector<Unit> virtualBrick)
 {
     QVector<Unit> virtualFood;
     virtualFood.append(QVsnake[0]);
     return QSbfs(virtualFood,virtualBrick);
 }

 bool aiSnake::QSai(QVector<Unit> virtualFood,QVector<Unit> virtualBrick)
 {
     int eatflag;
     int sheadx=QVsnake[0].getUnitX();
     int sheady=QVsnake[0].getUnitY();

     /*virtual snake*/
     aiSnake snake(sheadx,sheady,1,this->Sdirection,theme);
     snake.QVsnake.clear();
     for(int i=0;i<QVsnake.size();++i)
     {
         snake.QVsnake.append(QVsnake[i]);
     }

     /*simulate bfs search*/
     while((eatflag=snake.QSeat(virtualFood))==-1)
     {
         if(snake.QSbfs(virtualFood,virtualBrick)==false)
            break;
         snake.QSmove();
     }

     /*food can be eat,and snake can follow tail after eat food*/
     if(eatflag!=-1&&snake.followTail(virtualBrick)==true)
     {
          return QSbfs(virtualFood,virtualBrick);
     }

     /*handle by followTail function directly,as it will handle the case that tail can't be followed*/
     return followTail(virtualBrick);
 }
