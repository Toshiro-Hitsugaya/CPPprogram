#include "enemybase.h"

enemybase::enemybase(double hp):HP(hp), live(true)
{

}

inline void enemybase::attacked(double d)
{
    if(live) HP-=d;
    if(HP<0){
        HP=0;
        live=false;
    }
}

inline void enemybase::reduceSpeed(double d)
{
    speed-=d;
}

inline double enemybase::get_x()
{
    return 0;
}

inline double enemybase::get_y()
{
    return 0;
}

enemybase::~enemybase()
{
}
