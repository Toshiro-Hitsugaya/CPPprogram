#ifndef DEF_H
#define DEF_H
#define CELLSIZE 60
class Coor
{
public:
    double x;
    double y;
    Coor(double x, double y){
        this->x=x;
        this->y=y;
    }
};
#define MAX_R 100
#define MAX_C 100

#define LEVEL_0 0
#define LEVEL_1 1

#define R_0 30.0
#define R_1 2.0

#define DURATION_0 20.0
#define DURATION_1 50.0


#define FIRE 100
#define FIRE_DPH_0 5.0
#define FIRE_DPH_1 10.0

#define ICE 101
#define DECELERATION_0 5.0
#define DECELERATION_1 8.0
#define ICE_DPH 300.0

#define SPEED_0 5
#define MIN_SPEED_0 1

#define BULL_R 30.0
#define MONSTER_WIDTH 30.0
#define MONSTER_HEIGHT 60.0

#define LAYER_BACKGROUND -1
#define LAYER_CIRCLE 0
#define LAYER_MONSTER 1
static int level;
static int goldCount;
#endif
