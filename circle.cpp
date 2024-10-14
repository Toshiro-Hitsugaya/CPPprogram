#include "circle.h"

circle::circle(double x, double y, int type, QList<Monster*> &monsters, QGraphicsScene* scene):center(x, y), monsters(monsters), SCENE(scene)
{
    fire=type==FIRE;
    ice=type==ICE;

    if(fire)
        CircleImage=QPixmap(":/res_of_qt/circle_fire.jpg");
    else if(ice)
        CircleImage=QPixmap(":/res_of_qt/circle_ice_0.jpg");

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

    start_duration();
}

inline bool circle::isIn(double x, double y)
{

    double dx = x - center.x;
    double dy = y - center.y;
    double distanceSqr = dx * dx + dy * dy;
    double RSqr = R * R;
    return distanceSqr - RSqr < 0;
}

inline void circle::start_duration()
{
    setPos(center.x-R, center.y-R);
    setPixmap(CircleImage);
    setZValue(LAYER_CIRCLE);
    SCENE->addItem(this);
    setTransformOriginPoint(pixmap().width() / 2, pixmap().height() / 2);
    QTimer* timer_zoom = new QTimer();
    connect(timer_zoom, &QTimer::timeout, this, [=]()  {
        static double scale = 0.0;
        scale += 0.005;
        if (scale >= 1.0) {
            scale = 1.0;
            timer_zoom->stop();
        }
        setScale(scale);
    });
    timer_zoom->start(10);
    if(fire){
        // QTimer* timer = new QTimer();
        // connect(timer, &QTimer::timeout, [=]() mutable {
        //     static double angle = 0.0;
        //     double radians = qDegreesToRadians(angle);

        //     double x = center.x + R * qCos(radians) - graphicsItem->pixmap().width() / 2;
        //     double y = center.y + R * qSin(radians) - graphicsItem->pixmap().height() / 2;
        //     graphicsItem->setPos(x, y);

        //     angle += 1.0;
        //     if (angle >= 360.0) angle -= 360.0;
        // });

        // timer->start(16);
        //graphicsItem->setTransformOriginPoint(graphicsItem->pixmap().width() / 2, graphicsItem->pixmap().height() / 2);
        QTimer* timer_rotation = new QTimer();
        connect(timer_rotation, &QTimer::timeout, this, [=](){
            static double angle = 0.0;
            setRotation(angle);
            angle += 5.0;
            if (angle >= 360.0) angle -= 360.0;
        });
        timer_rotation->start(16);
        QTimer::singleShot(duration * 1000 - 2000, this, [=]() {
            disconnect(timer_zoom, nullptr, this, nullptr);
            connect(timer_zoom, &QTimer::timeout, this, [=]()  {
                static double scale = 1.0;
                scale -= 0.005;
                if (scale <= 0.0) {
                    scale = 0.0;
                    timer_zoom->stop();
                }
                setScale(scale);
            });
            timer_zoom->start(10);
        });
    }else if(ice){
        QTimer::singleShot(duration * 500, this, [=]() {
            CircleImage=QPixmap(":/res_of_qt/circle_ice_1.jpg");
            setPixmap(CircleImage);
            //graphicsItem->setTransformOriginPoint(graphicsItem->pixmap().width() / 2, graphicsItem->pixmap().height() / 2);
        });
        QTimer::singleShot(duration * 750, this, [=]() {
            CircleImage=QPixmap(":/res_of_qt/circle_ice_2.jpg");
            setPixmap(CircleImage);
            //graphicsItem->setTransformOriginPoint(graphicsItem->pixmap().width() / 2, graphicsItem->pixmap().height() / 2);
        });
        QTimer::singleShot(duration * 1000-500, this, [=]() {
            CircleImage=QPixmap(":/res_of_qt/circle_ice_3.jpg");
            setPixmap(CircleImage);
            //graphicsItem->setTransformOriginPoint(graphicsItem->pixmap().width() / 2, graphicsItem->pixmap().height() / 2);
        });
    }




    QTimer::singleShot(duration * 1000, this, [=]() {
        this->deleteLater();
        SCENE->removeItem(this);
    });



    QTimer* Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, [=]() {
        for(auto &i:monsters){
            if(fire)
                fire_attack(i);
            else if(ice)
                decelerate(i);
        }
    });
    Timer->start(10);
}

inline void circle::fire_attack(Monster* M)
{
    if (isIn(M->get_x(), M->get_y()))
        M->takeDamage(fire_dps);
}
inline void circle::decelerate(Monster* M)
{
    if (isIn(M->get_x(), M->get_y()))
        M->takeDeceleration(1.0); // 对怪物造成伤害
    else
        M->takeDeceleration(0.0);
}
circle::~circle()
{
    if(ice)
        for(Monster *i:monsters){
            i->takeDeceleration(0.0);
            if(isIn(i->get_x(), i->get_y()))
                i->takeDamage(ICE_DPH);
        }
}
