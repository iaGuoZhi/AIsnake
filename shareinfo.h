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

class shareinfo
{
public:
    shareinfo();
};

#endif // SHAREINFO_H
