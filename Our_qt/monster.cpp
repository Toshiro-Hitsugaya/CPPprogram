#include "Monster.h"

Monster::Monster(double hp, int speed, int gold, QObject *parent)
    : QObject(parent), HP(hp), speed(speed), gold_getted(gold), x(70), y(0), direction(0), moveStep(0) {
    // monster_Image.load(":/res_of_qt/Shu.gif"); // 怪的图片

    movie = new QMovie(":/res_of_qt/HUHUHU.gif"); // 添加这一行
    movie->start(); // 开始动画

    // 行走计时器
    movement_Timer = new QTimer(this);
    connect(movement_Timer, &QTimer::timeout, this, &Monster::move);
    movement_Timer->start(100); // 0.1秒前进一次
}

Monster::~Monster() {
    delete movement_Timer;
    delete movie;
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

    if (moveStep < 150 + 30) {
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 150 + 30 && moveStep < 313 +30){
        x += speed;
        moveStep += speed;
    }
    else if (moveStep >= 313 +30 && moveStep < 373+30){
        y -= speed;
        moveStep += speed;
    }
    else if (moveStep >= 373+30 && moveStep < 688 +30){
        x +=speed;
        moveStep += speed;
    }
    else if (moveStep >= 688+30 && moveStep < 748+30){
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 748 +30){
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
    setRect(x, y, 50, 70);
}

void Monster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // QRect drawRect = rect().toRect(); // 将 QRectF 转换为 QRect
    // QSize size = drawRect.size(); // 获取 QRect 的大小

    // 绘制怪物图像
    if (HP > 0){
        // 设置目标大小 50*70好像挺不错，记得改update
        QSize targetSize(50, 70); // 目标宽度和高度

        // // 使用 scaled() 方法调整图像大小
        // QPixmap scaledImage = monster_Image.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // // 绘制调整大小后的图像
        // QRect targetRect(x, y, scaledImage.width(), scaledImage.height());
        // painter->drawPixmap(targetRect, scaledImage);

        QImage currentFrame = movie->currentImage().scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 使用当前帧

        QRect targetRect(x, y, currentFrame.width(), currentFrame.height());
        painter->drawImage(targetRect, currentFrame); // 使用 drawImage 绘制
    }

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
