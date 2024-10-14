#ifndef RAMPAGEMONSTER_H
#define RAMPAGEMONSTER_H

#include "Monster.h"

class RampageMonster : public Monster
{
    Q_OBJECT
public:
    RampageMonster(double hp, int speed, int gold, QObject *parent = nullptr);
    void move() override; // 重写父类的move方法
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
};

#endif // RAMPAGEMONSTER_H
