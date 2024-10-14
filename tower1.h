#ifndef TOWER1_H
#define TOWER1_H

#include "towerbase.h"
#include <QGraphicsScene>
class BulletStr :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    friend class tower1;

    Coor bull_center;
    double k = 0.0, b = 0.0;    //用于计算出子弹路径
    bool dirFlag = false;       //移动方向标识
    QGraphicsScene* scene;
    //子弹构造
    QPixmap BullImage;
    QTimer* Timer;
public:
    BulletStr(double x, double y, QGraphicsScene* scene) :bull_center(x,y) , scene(scene), Timer (new QTimer()){
        setPos(bull_center.x-BULL_R, bull_center.y-BULL_R);
        BullImage=QPixmap(":/res_of_qt/circle_fire.jpg");
        setPixmap(BullImage);
        setZValue(LAYER_CIRCLE);
        scene->addItem(this);
        connect(Timer, &QTimer::timeout, this, &BulletStr::update);
        Timer->start(100);

    }
    ~BulletStr(){
        scene->removeItem(this);
    }
    void update(){
        setPos(bull_center.x-BULL_R, bull_center.y-BULL_R);
    }
};
class tower1 : public towerBase,public QGraphicsItem
{
private:
    QList<Monster*> &monsters;
    QGraphicsScene* scene;
    QList<BulletStr*> BulletVec;  //子弹数组
public:
    tower1(const int, const int, QList<Monster*> &monsters, QGraphicsScene* scene);
    QTimer *timeAttack;
    QPixmap tower1_Image; // 添加塔图像成员
    QRectF boundingRect() const override {
        // 返回一个矩形，表示这个图形项的边界
        return QRectF(0, 0, 650, 350); // 全屏
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void Attack(QVector<Monster*>&) override;  //重写攻击函数
    int DistBetPoints(int x1,int y1,int x2,int y2){
        return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
    }
    bool isInRange(Monster* monster);
    QList<Monster*> getMonstersInRange();
    void startTowerAttack();
};

#endif // TOWER1_H
