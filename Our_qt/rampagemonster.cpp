#include "rampagemonster.h"

RampageMonster::RampageMonster(double hp, int speed, int gold, QObject *parent)
    : Monster(hp, speed, gold, parent) {
    monster_Image.load(":/res_of_qt/KeAiNie.png"); // 怪的图片
}

void RampageMonster::move() {
    if (moveStep < 150 ) {
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 150  && moveStep < 313){
        x += speed;
        moveStep += speed;
    }
    else if (moveStep >= 313 && moveStep < 373 ){
        y -= speed;
        moveStep += speed;
    }
    else if (moveStep >= 373 && moveStep < 688){
        x +=speed;
        moveStep += speed;
    }
    else if (moveStep >= 688 && moveStep < 748){
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 748){
        emit monsterKilled(0);
    }
    update();
}

void RampageMonster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QSize targetSize(50, 70); // 目标宽度和高度
    QPixmap scaledImage = monster_Image.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);    // 使用 scaled() 方法调整图像大小
    QRect targetRect(x, y, scaledImage.width(), scaledImage.height());
    painter->drawPixmap(targetRect, scaledImage);

    //画血条
    if (HP > 40.0)
        painter->setBrush(Qt::yellow);
    else
        painter->setBrush(Qt::red);
    if (HP > 0)
        painter->drawRect(rect().x(), rect().y() - 2, rect().width() * (HP / 100.0), 5);
}
