#ifndef CIRCLE_H
#define CIRCLE_H
#include <def.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <monster.h>

class circle:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    Coor center;
    double duration;
    double R;
    QPixmap CircleImage; // 图像
    QList<Monster*> &monsters;
    QGraphicsScene* SCENE;

    bool fire;
    double fire_dps;

    bool ice;
    double deceleration;


public:
    circle(double x, double y, int type, QList<Monster*> &monsters, QGraphicsScene* scene);
    bool isIn(double x, double y);
    void start_duration();
    void fire_attack(Monster* M);
    void decelerate(Monster* M);
    ~circle();
};
#endif

