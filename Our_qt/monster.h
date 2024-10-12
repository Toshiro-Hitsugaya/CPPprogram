#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QMovie>

class Monster : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    // 血条，速度，金币
    Monster(double hp, int speed, int gold, QObject *parent = nullptr);
    ~Monster();

    void move();
    void takeDamage(double damage); // 受伤
    bool isDead() const;
    void update(); // 更新位置
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // 画怪本身和血条

    int get_x(){
        return x;
    }
    int get_y(){
        return y;
    }

signals:
    void monsterKilled(int gold); // 嘎了发信号，给金币

protected:
    double HP;
    int speed;
    int x;
    int y;
    int direction; // 0下, 1右, 2上，3左，但是也不用这样
    int gold_getted;
    int moveStep;
    QTimer *movement_Timer; // 出怪间隔

private:
    void checkDeath();
    QPixmap monster_Image; // 添加怪物图像成员
    QMovie *movie; // 添加一个 QMovie 对象
};

#endif // MONSTER_H
