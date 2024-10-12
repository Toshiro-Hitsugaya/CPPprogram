#include "towerbase.h"

towerBase::towerBase(QWidget *parent)
    : QObject{parent}
{

}

//构造函数初始化坐标
towerBase::towerBase(const int x, const int y)
{
    disCoorX = x, disCoorY = y;    //将防御塔真实坐标赋给显示坐标
}

Coor towerBase::getCoor() const      //返回防御塔坐标
{
    return Coor(disCoorX, disCoorY);
}

QString towerBase::getPicturePath() const//返回防御塔图片路径
{
    return picturePath;
}

int towerBase::getWidth() const     //返回防御塔宽高
{
    return width;
}

int towerBase::getHeight() const
{
    return height;
}

double towerBase::getAngle() const     //返回防御塔角度
{
    return angle;
}

int towerBase::getRange() const      //返回防御塔攻击范围
{
    return range;
}

Monster* towerBase::getTargetEnemy() const      //返回目标敌人
{
    return targetEnemy;
}

QVector<Coor> towerBase::getAttackCoor() const  //返回攻击坐标
{
    QVector<Coor> tempAttackec;
    for(auto bull : BulletVec)  //遍历子弹数组，把子弹数组的坐标全部给临时数组
        tempAttackec.push_back(Coor(bull->x, bull->y));

    return tempAttackec;    //返回
}

int towerBase::getAttackPower() const     //返回防御塔攻击力
{
    return attackPower;
}

int towerBase::getValue() const           //返回防御塔价值
{
    return value;
}

bool towerBase::getRangeFlag() const      //返回显示范围标记
{
    return displayRangeFlag;
}

int towerBase::getAttackInterval() const  //返回攻击间隔
{
    return attackInterval;
}

Coor towerBase::getDisCoor() const        //返回防御塔显示坐标
{
    return Coor(disCoorX, disCoorY);
}

int towerBase::getUpgradeValue() const    //返回升级成本 *
{
    return upgradeValue;
}

void towerBase::setCoor(const int x, const int y)         //设置防御塔坐标
{
    this->disCoorX = x, this->disCoorY = y;
}

void towerBase::setWidthHeight(const int width, const int height)  //设置防御塔宽高
{
    this->width = width, this->height = height;
}

void towerBase::setAngle(const double angle)       //设置防御塔旋转角度
{
    this->angle = angle;
}

void towerBase::setTargetEnemyNull()               //设置目标敌人为空
{
    targetEnemy = nullptr;
}

void towerBase::setRangeFlag(const bool flag)      //设置显示范围标记
{
    displayRangeFlag = flag;
}

void towerBase::setAttackInterval(const int attackInterval) //设置攻击间隔
{
    this->attackInterval = attackInterval;
}

void towerBase::setValue(const int value)                   //设置防御塔价值   *
{
    this->value = value;
}

void towerBase::setAttackPower(const int attackPower)       //设置防御塔攻击力  *
{
    this->attackPower = attackPower;
}

void towerBase::setDisCoor(const int x, const int y)      //设置显示坐标    *
{
    disCoorX = x, disCoorY = y;
}

void towerBase::setUpgradeValue(const int upgradeValue)   //设置防御塔升级成本 *
{
    this->upgradeValue = upgradeValue;
}

void towerBase::setRange(const int range)                 //设置防御塔攻击范围 *
{
    this->range = range;
}
