#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <def.h>
class Monster : public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    // 血条，速度，金币
    Monster(int hp, int speed, int gold, QGraphicsScene* scene, QList<Monster*>& monsters);
    ~Monster();

    void move();
    void takeDamage(double damage); // 受伤
    void takeDeceleration(double deceleration);
    bool isDead() const;
    void update(); // 更新位置
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // 画怪本身和血条
    double get_x();
    double get_y();

signals:
    void monsterKilled(int); // 嘎了发信号，给金币

protected:
    int HP;
    double speed;
    double x;
    double y;
    int direction; // 0下, 1右, 2上，3左，但是也不用这样
    int gold_getted;
    int moveStep;
    QTimer *movement_Timer; // 出怪间隔
    QGraphicsScene* scene;
    QList<Monster*>& monsters;
private:
    void checkDeath();
    QPixmap monster_Image; // 添加怪物图像成员
};

#endif // MONSTER_H
