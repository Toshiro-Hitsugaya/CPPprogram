#include "MainWindow.h"
#include "Monster.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <Qstring>
#include <QVBoxLayout>
#include <QDebug>
#include "tower1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), spawnTimer(new QTimer(this)),goldCount(50) {
    setupScene(); // 设置场景

    // 出怪时间，设置定时器每两秒发射一次信号
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnMonster);
    spawnTimer->start(2000);

    startTowerAttack();
}

MainWindow::~MainWindow() {
    delete scene;
    delete spawnTimer;   
    for (auto i:towers){
        delete i;
    }
}

void MainWindow::setupScene() {
    // 主视图
    // 设置场景大小和窗口大小  650*350
    const int sceneWidth = 650; // 新场景宽度
    const int sceneHeight = 350; // 新场景高度
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight); // 设置场景大小
    QGraphicsView *view = new QGraphicsView(scene); // 创建图形视图
    setCentralWidget(view);

    // 画个背景
    QPixmap background(":/res_of_qt/new_background.png");
    QPixmap scaledBackground = background.scaled(sceneWidth, sceneHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(scaledBackground);
    backgroundItem->setPos(0, 0);
    backgroundItem->setZValue(-1); // 防止覆盖
    scene->addItem(backgroundItem);

    // QPixmap Tower3(":/res_of_qt/star.png");
    // QPixmap Tower_new3 = Tower3.scaled(50, 50);
    // QGraphicsPixmapItem *TowerItem3 = new QGraphicsPixmapItem(Tower_new3);
    // TowerItem3 -> setPos(301, 181);
    // TowerItem3 -> setZValue(0);
    // scene->addItem(TowerItem3);

    // 画显示金币
    goldLabel = new QLabel(this);
    goldLabel->setText("金币: " + QString::number(goldCount));
    goldLabel->setStyleSheet("QLabel { font-size: 16px; color: yellow; }");
    goldLabel->setGeometry(view->width() - 120, 10, 100, 30);
    goldLabel->raise(); // 确保在其他组件上方
}

void MainWindow::spawnMonster() {
    // 血量，速度，金币
    Monster *monster = new Monster(100.0, 5, 10);

    // // 处理走到边界外的怪物
    // if (monster->get_x() == 650){
    //     removeMonster(monster);
    // }

    //这里接到信号了
    connect(monster, &Monster::monsterKilled, this, [this, monster](int gold) {
        goldCount += gold; // 增加金币数
        goldLabel->setText("金币: " + QString::number(goldCount)); // 更新显示
        removeMonster(monster); // 移除死亡的怪物
    });

    scene->addItem(monster);
    allMonsters.append(monster); // 将怪物添加到怪物列表
}

bool MainWindow::canPlaceTower(int x, int y) {
    // 在此检查点击的点是否合适放置塔
    // 例如，可以通过坐标检查是否与其他塔重叠，或者是否在道路上
    // 对塔的坐标约束都可以补充在这里
    for(auto tower: towers){
        int towerX = tower->getCoor().x;
        int towerY = tower->getCoor().y;
        if (x >= towerX - 40 && x <= towerX + 40 && y <= towerY + 40 && y >= towerY - 40){
            return false;
        }
    }
    return true;
}

// 金币限制放置
void MainWindow::placeTower(int x, int y) {
    tower1* newTower = new tower1(x, y);
    if (goldCount >= newTower->getValue()){
        towers.append(newTower); // 将塔添加到列表中
        goldCount -= newTower->getValue();
        goldLabel->setText("金币: " + QString::number(goldCount)); // 更新显示
        scene->addItem(newTower);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    int x = event->position().x();
    int y = event->position().y();

    // // 检查点击的位置是否可以放置塔
    if (canPlaceTower(x, y)) {
        placeTower(x, y);
    }
}

// 对范围内的怪物进行攻击
void MainWindow::startTowerAttack() {
    QTimer *attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, this, [this]() {
        for (tower1* tower : towers) {
            QVector<Monster*> monstersInRange = getMonstersInRange(tower);
            tower->Attack(monstersInRange);
        }
    });
    attackTimer->start(1000); // 每秒攻击一次
}

QVector<Monster*> MainWindow::getMonstersInRange(tower1* tower) {
    QVector<Monster*> monstersInRange;
    for (Monster* m : allMonsters) {
        if (isInRange(tower, m)) {
            monstersInRange.append(m); // 将在范围内的怪物添加到结果中
        }
    }
    return monstersInRange;
}

bool MainWindow::isInRange(tower1* tower, Monster* monster) {
    // 获取塔和怪物的坐标
    int towerX = tower->getCoor().x;
    int towerY = tower->getCoor().y;
    int monsterX = monster->get_x();
    int monsterY = monster->get_y();

    // 计算塔和怪物之间的距离
    int deltaX = towerX - monsterX;
    int deltaY = towerY - monsterY;
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    // 检查是否在塔的攻击范围内
    return distance <= tower->getRange();
}

// 这个先等一下
void MainWindow::removeMonster(Monster* monster) {
    allMonsters.removeOne(monster); // 从怪物列表中移除
    scene->removeItem(monster); // 从场景中移除
}
