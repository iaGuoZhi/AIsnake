#define QT_NO_OPENGL
#include "snakeboard.h"

#include <QtWidgets>
#include<QDebug>
#include<QString>

snakeboard::snakeboard(QWidget *parent)
    : QFrame(parent)
{
   init();
}

void snakeboard::init()
{
    setFocusPolicy(Qt::StrongFocus);
    state=WAIT;
    command=EMPTY;
}



void snakeboard::pause()
{
    if(state==RUN)
    {
        state=PAUSE;
        return;
    }
    if(state==PAUSE)
    {
        state=RUN;
    }
}

void snakeboard::help()
{
    if(command!=HELP)
    command=HELP;
    else
    {
        command=EMPTY;
    }
}
void snakeboard::paintMessage(QPaintEvent *)
{
    QPainter p;
    p.begin(this);
    QFont font("宋体",15,QFont::Bold,true);
    p.setFont(font);
    p.setPen(Qt::green);
    if(command==HELP)
    {
        p.drawText(20,20,"这是一个充满挑战的小游戏");
        p.drawText(20,60,"游戏模式：单人游戏，双人游戏，人机PK，观战模式");
        p.drawText(20,100,"操作说明：单人模式 或者　玩家一  方向键控制移动  Shift键隐身；　　玩家二　AWSD控制方向　Ｑ键隐身");
        p.drawText(20,140,"规则说明");
        p.drawText(20,180,"       1.每次吃到食物会得分，得分越高，等级越高，移动速度越快；");
        p.drawText(20,220,"       2.当蛇咬到自己或者头部撞到墙壁，或者头部与被自己长的蛇的头部相碰时死亡");
        p.drawText(20,260,"       3.在双人对战模式下吃到特定食物时，玩家会具有隐身的能力");
        p.drawText(20,300,"       4.观战模式中，系统将用算法操纵蛇的移动，达到最短路径寻找食物，自动避免障碍物的效果");
        p.drawText(20,340,"       5.人机对战中，AI未解锁隐身、截获功能");
        p.drawText(20,380,"       6.双人游戏中，蛇具有截获蛇身的能力，如果蛇头咬到其他蛇的蛇身，则被咬蛇的蛇身之后的长度将移动至该蛇");
        p.drawText(20,420,"       6.双人游戏中，如果两个蛇头相触，则蛇身短的蛇死亡");
        p.drawText(20,460,"游戏主题：地图，世界杯，校园");
    }
    else{
        if(state==WAIT)
        {
            p.drawText(20,20,"are you ready?");
        }
        if(state==END)
        {
            p.drawText(20,20,tr("END"));
        }
        if(state==PAUSE)
        {
            p.drawText(20,20, tr("Pause"));
        }
    }

    p.end();
}







