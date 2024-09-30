#include <def.h>
#include <monster.h>
class Coor
{
public:
    double x;
    double y;
    Coor(double x, double y){
        this->x=x;
        this->y=y;
    }
};

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
    circle(double x, double y, int type, const QPixmap& image, QGraphicsScene* scene);
    bool isIn(double x, double y);
    void start_duration();
    void fire_attack(Monster& M);

    Coor getTopLeftCorner() const {
        return Coor(center.x - R, center.y - R);
    }

    Coor getBottomRightCorner() const {
        return Coor(center.x + R, center.y + R);
    }
    ~circle();
};

circle::circle(double x, double y, int type, const QPixmap& image, QGraphicsScene* scene):center(x, y), CircleImage(image), graphicsItem(new QGraphicsPixmapItem(image))
{
    scene->addItem(graphicsItem);
    fire=type==FIRE;
    ice=type==ICE;
    switch (level)
    {
    case LEVEL_0:
        duration=DECELERATION_0;
        R=R_0;
        fire_dps=FIRE_DPS_0;
        deceleration=DECELERATION_0;
        break;
    case LEVEL_1:
        duration=DECELERATION_1;
        R=R_1;
        fire_dps=FIRE_DPS_1;
        deceleration=DECELERATION_1;
        break;
    default:
        break;
    }
}

inline bool circle::isIn(double x, double y)
{
    
        int dx = x - center.x;
        int dy = y - center.y;
        int distanceSqr = dx * dx + dy * dy;
        int RSqr = R * R;
        return distanceSqr < RSqr;
}

inline void circle::start_duration()
{
    QTimer::singleShot(duration * 1000, this, [this]() {
        this->~circle();
    });
}

inline void circle::fire_attack(Monster& M)
{
    QTimer* attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, this, [this, &M, attackTimer]() {
            if (isIn(M.get_x(), M.get_y())) 
                M.takeDamage(fire_dps); // 对怪物造成伤害
        });
    attackTimer->start(1000); // 每秒触发一次
}

circle::~circle()
{
    graphicsItem->hide();
}
