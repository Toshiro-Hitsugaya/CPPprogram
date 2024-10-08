#include "circle.h"

circle::circle(double x, double y, int type, QList<Monster*> &monsters, const QPixmap& image, QGraphicsScene* scene):center(x, y), CircleImage(image), graphicsItem(new QGraphicsPixmapItem(image))
{
    fire=type==FIRE;
    ice=type==ICE;
    switch (level)
    {
    case LEVEL_0:
        duration=DURATION_0;
        R=R_0;
        fire_dps=FIRE_DPH_0;
        deceleration=DECELERATION_0;
        break;
    case LEVEL_1:
        duration=DURATION_1;
        R=R_1;
        fire_dps=FIRE_DPH_1;
        deceleration=DECELERATION_1;
        break;
    default:
        break;
    }
    graphicsItem->setPos(x-R, y-R);
    scene->addItem(graphicsItem);
    start_duration(monsters);
}

inline bool circle::isIn(double x, double y)
{

    double dx = x - center.x;
    double dy = y - center.y;
    double distanceSqr = dx * dx + dy * dy;
    double RSqr = R * R;
    return distanceSqr - RSqr < 0;
}

inline void circle::start_duration(QList<Monster*> &monsters)
{
    QTimer::singleShot(duration * 1000, this, [this]() {
        this->deleteLater();
    });
    QTimer* Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, [this, &monsters]() {
        for(auto &i:monsters){
            fire_attack(i);
        }
    });
    Timer->start(10);
}

inline void circle::fire_attack(Monster* M)
{
    if (isIn(M->get_x(), M->get_y()))
        M->takeDamage(fire_dps); // 对怪物造成伤害
}

circle::~circle()
{
    graphicsItem->hide();
}
