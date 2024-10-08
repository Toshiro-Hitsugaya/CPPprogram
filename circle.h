#include <def.h>
#include <monster.h>
#include <QPainter>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsScene>

class circle:public QObject
{
    Q_OBJECT
private:
    Coor center;
    double duration;
    double R;
    QPixmap CircleImage; // 圈图像
    QGraphicsPixmapItem* graphicsItem; // 图像项

    bool fire;
    double fire_dps;

    bool ice;
    double deceleration;


public:
    circle(double x, double y, int type, QList<Monster*> &monsters, const QPixmap& image, QGraphicsScene* scene);
    bool isIn(double x, double y);
    void start_duration(QList<Monster*> &monsters);
    void fire_attack(Monster* M);
    ~circle();
};

