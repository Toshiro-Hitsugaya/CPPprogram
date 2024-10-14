#include "tower1.h"

tower1::tower1(const int x, const int y) : towerBase(x, y)
{
    tower1_Image.load(":/res_of_qt/crystal.png");
    width = 110, height = 80;   //防御塔宽高
    // picturePath = ":/res/star.png";    //防御塔图片路径
    range = 100;        //攻击范围
    attackPower = 15;             //攻击力
    value = 15;
    attackInterval = 3; //攻击间隔
}

void tower1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 绘制图形项
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QSize targetSize(50, 70); // 目标宽度和高度
    // 使用 scaled() 方法调整图像大小
    QPixmap scaledImage = tower1_Image.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 绘制调整大小后的图像
    QRect targetRect(disCoorX - 25, disCoorY - 35, scaledImage.width(), scaledImage.height());
    painter->drawPixmap(targetRect, scaledImage);
}

// 补充，原本的被我注释了，这个全部攻击，用于调试
void tower1::Attack(QVector<Monster*>& enemyVec)
{
    for (auto enemyIt = enemyVec.begin(); enemyIt != enemyVec.end(); ++enemyIt) {
        (*enemyIt)->takeDamage(attackPower);
    }
}

// //攻击函数
// void tower1::Attack(QVector<Monster*>& enemyVec)
// {
//     if(attackInterval < 1) attackInterval = 1;  //防御塔攻速上限

//     //子弹移动
//     for(auto bull : BulletVec)
//     {
//         bull->dirFlag ? bull->x += 8 : bull->x -= 8;    //x轴增加

//         bull->y = bull->k * bull->x + bull->b;          //y随x改变
//     }

// //     //遍历删除攻击范围外的子弹
// //     for(auto bullit = BulletVec.begin(); bullit != BulletVec.end(); bullit++)
// //         if(DistBetPoints((*bullit)->x + 15, (*bullit)->y + 15, x + halfBlockLen, y + halfBlockLen) > range) //子弹和防御塔之间的距离
// //         {
// //             delete *bullit;
// //             BulletVec.erase(bullit);
// //             break;
// //         }

// //     if(enemyVec.empty()) return;    //敌人数组为空直接返回

// //     //敌人受到攻击
// //     for (auto bullIt = BulletVec.begin(); bullIt != BulletVec.end(); bullIt++)        //子弹
// //         for (auto enemyIt = enemyVec.begin(); enemyIt != enemyVec.end(); enemyIt++)   //敌人
// //             if ((*bullIt)->x + 15 >= (*enemyIt)->getCoor().x && (*bullIt)->x <= (*enemyIt)->getCoor().x + (*enemyIt)->getWidth() &&
// //                 (*bullIt)->y + 15 >= (*enemyIt)->getCoor().y && (*bullIt)->y <= (*enemyIt)->getCoor().y + (*enemyIt)->getHeight())
// //             {
// //                 //击中敌人则减掉敌人血量并删除子弹
// //                 //(*enemyIt)->setHealth((*enemyIt)->getHealth() - attackPower);

// //                 //向数组中插入击中效果对象
// //                 //hitEffectVec.push_back(new HitEffect((*enemyIt)->getCoor().x + ((*enemyIt)->getWidth() >> 1),
// //                                                      //(*enemyIt)->getCoor().y + ((*enemyIt)->getHeight() >> 1), 80, 80));

// //                 delete *bullIt;
// //                 BulletVec.erase(bullIt);

// //                 goto outLoop;
// //             }
// // outLoop:

// //     if (!targetEnemy)       //目标敌人为空且敌人数组不为空
// //         targetEnemy = enemyVec.at(enemyVec.size() - 1); //设置目标敌人为范围内最后一个敌人
// //     else
// //     {
// //         //设置防御塔的旋转角度
// //         angle = atan2 ( targetEnemy->getCoor().y - (y + halfBlockLen), targetEnemy->getCoor().x - (x + halfBlockLen) ) * 180 / 3.1415;

// //         if(counter >= attackInterval)    //counter大于一定值时创建子弹
// //         {
// //             BulletStr* bull = new BulletStr(x + halfBlockLen, y + halfBlockLen);

// //             if(!(targetEnemy->getCoor().x - bull->x))   //如果这个数为0则取消创建这个子弹
// //             {
// //                 delete bull;
// //                 bull = nullptr;
// //                 goto jumpout;
// //             }

// //             //计算k、b
// //             bull->k = (targetEnemy->getCoor().y - bull->y) / (targetEnemy->getCoor().x - bull->x);
// //             bull->b = targetEnemy->getCoor().y - targetEnemy->getCoor().x * bull->k;
// //             //确定移动方向
// //             if(bull->x < targetEnemy->getCoor().x) bull->dirFlag = true;  //是向左

// //             BulletVec.push_back(bull);  //插入到数组中

// //             counter = 0;

// //         jumpout:;
// //         }

// //         counter++;
// //         //如果目标怪物和防御塔的距离超过了射程则将目标怪物重新设为空
// //         if (DistBetPoints(targetEnemy->getCoor().x, targetEnemy->getCoor().y, x + halfBlockLen, y + halfBlockLen) > range)
// //             targetEnemy = nullptr;
// //     }
// }
