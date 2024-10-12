#ifndef TOWER1_H
#define TOWER1_H

#include "towerbase.h"

class tower1 : public towerBase,  public QGraphicsItem
{
public:
    QPixmap tower1_Image; // 添加塔图像成员
    tower1(const int, const int);
    void Attack(QVector<Monster*>&) override;  //重写攻击函数
    QRectF boundingRect() const override {
        // 返回一个矩形，表示这个图形项的边界
        return QRectF(0, 0, 650, 350); // 全屏
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int type() const override {
        // 返回图形项的类型，需要是一个唯一的整数值
        return UserType + 1;
    }
};

#endif // TOWER1_H
