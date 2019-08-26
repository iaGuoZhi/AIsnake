#ifndef UNIT_H
#define UNIT_H


class Unit
{
public:
    Unit()
    {}
    Unit(int x,int y,int color)
    {
        UnitX=x;
        UnitY=y;
        UnitColor=color;
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
private:
    int UnitX;
    int UnitY;
    int UnitColor;


};

#endif // UNIT_H
