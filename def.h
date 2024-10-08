#ifndef DEF_H
#define DEF_H
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
#define LEVEL_0 0
#define LEVEL_1 1

#define R_0 75.0
#define R_1 2.0


#define DURATION_0 100.0
#define DURATION_1 7.5


#define FIRE 100
#define FIRE_DPH_0 1.0
#define FIRE_DPH_1 10.0

#define ICE 101
#define DECELERATION_0 5.0
#define DECELERATION_1 8.0
static int level;
#endif
