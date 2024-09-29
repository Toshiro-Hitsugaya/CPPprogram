#include <def.h>
#include <Monster.h>
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

class circle
{
private:
    Coor center;
    double duration;
    double R;
    bool fire;
    double fire_dps;

    bool ice;
    double deceleration;
    

public:
    circle(double x, double y, int type);
    bool isIn(double x, double y);

    void fire_attack(Monster M);

    Coor getTopLeftCorner() const {
        return Coor(center.x - R, center.y - R);
    }

    Coor getBottomRightCorner() const {
        return Coor(center.x + R, center.y + R);
    }
    ~circle();
};

circle::circle(double x, double y, int type):center(x, y)
{
    fire=type==FIRE;
    ice=type==ICE;
    switch (level)
    {
    case LEVEL_0:
        duration=DECELERATION_0;
        R=R_0;
        fire_dps=FIRE_DPS_0;
        deceleration=DECELERATION_0;
        break;
    case LEVEL_1:
        duration=DECELERATION_1;
        R=R_1;
        fire_dps=FIRE_DPS_1;
        deceleration=DECELERATION_1;
        break;
    default:
        break;
    }
}

inline bool circle::isIn(double x, double y)
{
    
        int dx = x - center.x;
        int dy = y - center.y;
        int distanceSqr = dx * dx + dy * dy;
        int RSqr = R * R;
        return distanceSqr < RSqr;
}

inline void circle::fire_attack(Monster M)
{
    if(isIn(M.get_x(), M.get_y()))
        M.attacked(fire_dps);
}

circle::~circle()
{
}
