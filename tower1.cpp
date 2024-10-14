#include "tower1.h"
#include "QDebug"

using namespace std;
tower1::tower1(const int x, const int y, QList<Monster*> &monsters, QGraphicsScene* scene) : towerBase(x, y), monsters(monsters), scene(scene)
{
    tower1_Image.load(":/res/star.png");
    width = 110, height = 80;   //防御塔宽高
    picturePath = ":/res/star.png";    //防御塔图片路径
    range = 200;        //攻击范围
    attackPower = 400;             //攻击力
    value = 10;

    attackInterval = 10; //攻击间隔

    timeAttack = new QTimer();
    startTowerAttack();
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

//攻击函数
void tower1::Attack(QVector<Monster*>& enemyVec)
{
    qDebug() << "111111111";
    if(attackInterval < 1) attackInterval = 1;  //防御塔攻速上限

    //子弹移动
    qDebug() << "子弹数量" << BulletVec.count();
    for(auto bull : BulletVec)
    {
        bull->dirFlag ? bull->bull_center.x += 20.0 : bull->bull_center.x -= 20.0;    //x轴增加

        bull->bull_center.y = bull->k * bull->bull_center.x + bull->b;        //y随x改变
        qDebug() << bull->bull_center.x << bull->bull_center.y;
        qDebug() << "2";
    }

     //遍历删除攻击范围外的子弹
    for(BulletStr* i:BulletVec)
        if(sqrt(DistBetPoints(i->bull_center.x + 15, i->bull_center.y + 15, disCoorX, disCoorY)) > range) //子弹和防御塔之间的距离
        {
            if(i)
                delete i;
            BulletVec.removeOne(i);
            break;
        }

    qDebug() << "一";

    if(enemyVec.empty()){
        qDebug() << "敌人为空";
        return;    //敌人数组为空直接返回
    }
    qDebug() << "二";
    //敌人受到攻击
    for (auto i : BulletVec)        //子弹
        for (Monster* j:enemyVec)   //敌人
            if (i->bull_center.x >= (j->get_x() - MONSTER_WIDTH / 2) && i->bull_center.x <= (j->get_x() + MONSTER_WIDTH / 2) &&
                i->bull_center.y >= (j->get_y() - MONSTER_HEIGHT / 2)&& i->bull_center.y <= (j->get_y() + MONSTER_HEIGHT / 2))
            {
                qDebug() << "进入攻击判断";
                //击中敌人则减掉敌人血量并删除子弹
                j->takeDamage(attackPower);
                qDebug() << "扣血";

                //向数组中插入击中效果对象
                //hitEffectVec.push_back(new HitEffect((*enemyIt)->getCoor().x + ((*enemyIt)->getWidth() >> 1),
                                                     //(*enemyIt)->getCoor().y + ((*enemyIt)->getHeight() >> 1), 80, 80));
                delete i;
                BulletVec.removeOne(i);

                goto outLoop;
            }


    qDebug() << "三";
outLoop:

    if (!targetEnemy){
        //目标敌人为空且敌人数组不为空
        qDebug() << "正在找敌人";
        for (auto enemyIt = enemyVec.begin(); enemyIt != enemyVec.end(); enemyIt++){
            if(enemyIt != nullptr){
                if(sqrt(DistBetPoints((*enemyIt)->get_x(),(*enemyIt)->get_y(),disCoorX,disCoorY)) < range){
                    targetEnemy = (*enemyIt);
                    qDebug() << "找到敌人";
                }else{
                    qDebug() << (*enemyIt)->get_x() <<(*enemyIt)->get_y()<<disCoorX << disCoorY;
                    qDebug() << DistBetPoints((*enemyIt)->get_x(),(*enemyIt)->get_y(),disCoorX,disCoorY) << range;
                    qDebug() << "超出范围";
                }
            }
        }
    }else{
        // 设置防御塔的旋转角度
        // angle = atan2 ( targetEnemy->getCoor().y - (y + halfBlockLen), targetEnemy->getCoor().x - (x + halfBlockLen) ) * 180 / 3.1415;

        if(counter >= attackInterval)    //counter大于一定值时创建子弹
        {
            if((targetEnemy->get_x() - disCoorX))   //如果这个数为0则取消创建这个子弹
            {
                BulletStr* bull = new BulletStr(disCoorX, disCoorY, scene);
                bull->k = (targetEnemy->get_y() - bull->bull_center.y) / (targetEnemy->get_x() - bull->bull_center.x);
                bull->b = targetEnemy->get_y() - targetEnemy->get_x() * bull->k;
                //确定移动方向
                if(bull->bull_center.x < targetEnemy->get_x()) bull->dirFlag = true;  //是向左

                BulletVec.push_back(bull);  //插入到数组中

                counter = 0;
            }

        }

        counter++;
        //如果目标怪物和防御塔的距离超过了射程则将目标怪物重新设为空
        if (sqrt(DistBetPoints(targetEnemy->get_x(), targetEnemy->get_y(),disCoorX,disCoorY)) > range){
            targetEnemy = nullptr;
            qDebug() << "目标超出范围";
        }
    }
    qDebug() << "四";
}

// 对范围内的怪物进行攻击
void tower1::startTowerAttack() {
    QTimer *attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, this, [=]() {
            QVector<Monster*> monstersInRange = getMonstersInRange();
            Attack(monstersInRange);
    });
    attackTimer->start(100); // 每秒攻击一次
}

QList<Monster*> tower1::getMonstersInRange() {
    QVector<Monster*> monstersInRange;
    for (Monster* m : monsters) {
        if (isInRange(m)) {
            monstersInRange.append(m); // 将在范围内的怪物添加到结果中
        }
    }
    return monstersInRange;
}

bool tower1::isInRange(Monster* monster) {
    // 获取塔和怪物的坐标
    int towerX = disCoorX;
    int towerY = disCoorY;
    int monsterX = monster->get_x();
    int monsterY = monster->get_y();

    // 计算塔和怪物之间的距离
    int deltaX = towerX - monsterX;
    int deltaY = towerY - monsterY;
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    // 检查是否在塔的攻击范围内
    return distance <= range;
}
