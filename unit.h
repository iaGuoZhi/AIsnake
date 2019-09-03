#ifndef UNIT_H
#define UNIT_H
#include<QString>


enum UNITKIND{
    SNAKEHEAD,
    SNAKEBODY,
    FOODNORMAL,
    FOODSPECIAL,
    BRICK
} ;

class Unit
{
public:
    Unit()
    {}

    Unit(int x,int y,int color,UNITKIND unitKind)
    {
        UnitX=x;
        UnitY=y;
        UnitColor=color;
        this->unitKind=unitKind;
    }
    Unit(int x, int y, int color,UNITKIND unitKind,QString unitDescribe)
    {
        UnitX=x;
        UnitY=y;
        UnitColor=color;
        this->unitKind=unitKind;
        UnitDescribe=unitDescribe;
    }
    int getUnitX()
    {
        return UnitX;
    }
    int getUnitY()
    {
        return UnitY;
    }
    int getUnitColor()
    {
        return UnitColor;
    }
    void setUnitX(int x)
    {
        UnitX=x;
    }
    void setUnitY(int y)
    {
        UnitY=y;
    }
    void setUnitColor(int color)
    {
        UnitColor=color;
    }
    QString getUnitDescribe()
    {
        return UnitDescribe;
    }
    void setUnitDescribe(QString unitDEscribe)
    {
        this->UnitDescribe=unitDEscribe;
    }
    UNITKIND getUnitKind()
    {
        return unitKind;
    }
    void setUnitKind(UNITKIND unitKind)
    {
        this->unitKind=unitKind;
    }
private:
    int UnitX;
    int UnitY;
    int UnitColor;
    QString UnitDescribe="";
    UNITKIND unitKind;

};

#endif // UNIT_H
