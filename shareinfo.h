/************************************
 * this file is to keep the shared data structure
 * and data needed for different class
 **/
#ifndef SHAREINFO_H
#define SHAREINFO_H

enum GAMEMODE{
    SINGLEPLAYER,
    DOUBLEPLAYER,
    PLAYWITHAI,
    WATCHAIPLAY
};

enum THEME{
    COSTOM_FOREST,
    COSTOM_PIRARIE,
    COSTOM_SEA,
    SYSTEM_WINDOWS,
    SYSTEM_FUSION
};

enum DIFFICULTY{
    VERY_EASY,
    EASY,
    MEDIUM,
    HARD,
    VERY_HARD
};


enum{
    BOARDWIDTH=76,
    BOARDHEIGHT=64,
    BRICKWIDTH=7,
    BRICKHEIGHT=5
}; //set the amount of unit a board can hold
enum DIRECTION{
    RIGHT,DOWN,UP,LEFT
};

const int SNAKEHEADX=38;
const int SNAKEHEADY=30;
class shareinfo
{
public:
    shareinfo();
};

#endif // SHAREINFO_H
