#include "Monster.h"

Monster::Monster(int hp, int speed, int gold, QObject *parent)
    : QObject(parent), HP(hp), speed(speed), gold_getted(gold), x(80), y(0), direction(0), moveStep(0) {
    monster_Image.load(":/res_of_qt/monster.jpg"); // 怪的图片

    // 行走计时器
    movement_Timer = new QTimer(this);
    connect(movement_Timer, &QTimer::timeout, this, &Monster::move);
    movement_Timer->start(100); // 0.1秒前进一次
}

Monster::~Monster() {
    delete movement_Timer;
}

// move自定义的，按需求改路径，下面写的都是根据那个地图调试的
void Monster::move() {
    // switch (direction) {
    // case 0:
    //     if (moveStep < 190) {
    //         positionY += speed;
    //         moveStep += speed;
    //     } else {
    //         direction = 1;
    //         moveStep = 0;
    //     }
    //     break;
    // case 1:
    //     if (moveStep < 170) {
    //         positionX += speed;
    //         moveStep += speed;
    //     } else {
    //         direction = 2;
    //         moveStep = 0;
    //     }
    //     break;
    // case 2:
    //     if (moveStep < 50) {
    //         positionY -= speed;
    //         moveStep += speed;
    //     } else {
    //         direction = 0;
    //         moveStep = 0;
    //     }
    //     break;
    // }

    if (moveStep < 190) {
        y += speed;
        moveStep += speed;
        takeDamage(1);
    }
    else if (moveStep >= 190 && moveStep < 360){
        x += speed;
        moveStep += speed;
        takeDamage(0.7);
    }
    else if (moveStep >= 360 && moveStep < 420){
        y -= speed;
        moveStep += speed;
        takeDamage(3);
    }
    else if (moveStep >= 420 && moveStep < 750){
        x +=speed;
        moveStep += speed;
    }
    else if (moveStep >= 750 && moveStep < 815){
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 815){
        x +=speed;
    }
    update();
}

void Monster::takeDamage(double damage) {
    HP -= damage;
    checkDeath();
}

bool Monster::isDead() const {
    return HP <= 0;
}

void Monster::update() {
    setRect(x, y, 30, 30);
}

void Monster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRect drawRect = rect().toRect(); // 将 QRectF 转换为 QRect
    QSize size = drawRect.size(); // 获取 QRect 的大小

    // 绘制怪物图像
    if (HP > 0)
        painter->drawPixmap(drawRect, monster_Image.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //画血条
    if (HP > 40)
        painter->setBrush(Qt::green);
    else
        painter->setBrush(Qt::red);
    painter->drawRect(rect().x(), rect().y() - 2, rect().width() * (HP / 100.0), 5);
}

void Monster::checkDeath() {
    if (isDead()) {
        emit monsterKilled(gold_getted); // 发加金币信号
        delete this;
    }
}
