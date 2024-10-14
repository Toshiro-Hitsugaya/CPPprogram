#include "Monster.h"

Monster::Monster(double hp, int speed, int gold, QObject *parent)
    : QObject(parent), HP(hp), speed(speed), gold_getted(gold), x(70), y(0), direction(0), moveStep(0) {
    movie = new QMovie(":/res_of_qt/KD.gif"); // 添加这一行
    movie->start(); // 开始动画
    movie2 = new QMovie(":/res_of_qt/KDR.gif");
    movie2->start();

    // 行走计时器
    movement_Timer = new QTimer(this);
    connect(movement_Timer, &QTimer::timeout, this, &Monster::move);
    movement_Timer->start(100); // 0.1秒前进一次
}

Monster::~Monster() {
    // delete movement_Timer;这个可以移除，自动释放
    delete movie;
    delete movie2;
}

// move自定义的，按需求改路径，下面写的都是根据那个地图调试的
void Monster::move() {
    if (moveStep < 150) {
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 150  && moveStep < 313 ){
        x += speed;
        moveStep += speed;
    }
    else if (moveStep >= 313 && moveStep < 373){
        y -= speed;
        moveStep += speed;
    }
    else if (moveStep >= 373 && moveStep < 688 ){
        x +=speed;
        moveStep += speed;
    }
    else if (moveStep >= 688 && moveStep < 748){
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 748){
        emit monsterKilled(0); // 这里改了，最后也删了
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

    // 绘制怪物图像
    // 设置目标大小 50*70好像挺不错，记得改update
    QSize targetSize(50, 70); // 目标宽度和高度
    if (HP > 0 && HP < 40.0){
        QImage currentFrame2 = movie2->currentImage().scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 使用当前帧
        QRect targetRect2(x, y, currentFrame2.width(), currentFrame2.height());
        painter->drawImage(targetRect2, currentFrame2);
        speed = 9;
    }else{
        QImage currentFrame = movie->currentImage().scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 使用当前帧
        QRect targetRect(x, y, currentFrame.width(), currentFrame.height());
        painter->drawImage(targetRect, currentFrame); // 使用 drawImage 绘制
    }
    //画血条
    if (HP > 40.0)
        painter->setBrush(Qt::green);
    else
        painter->setBrush(Qt::red);
    painter->drawRect(rect().x(), rect().y() - 2, rect().width() * (HP / 100.0), 5);
}

void Monster::checkDeath() {
    if (isDead()) {
        emit monsterKilled(gold_getted); // 发加金币信号
    }
}
