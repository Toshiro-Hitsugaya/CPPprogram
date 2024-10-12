#include "enemybase.h"

monster::monster(double hp):HP(hp), live(true)
{
}

inline void monster::attacked(double d)
{
    if(live) HP-=d;
    if(HP<0){
        HP=0;
        live=false;
    }
}

inline void monster::reduceSpeed(double d)
{
    speed-=d;
}

inline double monster::get_x()
{
    return 0;
}

inline double monster::get_y()
{
    return 0;
}

monster::~monster()
{
}
