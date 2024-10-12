#ifndef ENEMYBASE_H
#define ENEMYBASE_H

class Coor
{
public:
    int x;
    int y;
    Coor(int a,int b){
        x = a;
        y = b;
    }
};

class monster
{
private:
    double HP;
    bool live;
    double speed;

public:
    monster(double hp);
    void attacked(double d);
    void reduceSpeed(double d);
    double get_x();
    double get_y();
    ~monster();
};

#endif // ENEMYBASE_H
