#include "MainWindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <Qstring>
#include <QVBoxLayout>
#include <QDebug>
#include <def.h>
#include <circle.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), spawnTimer(new QTimer(this)),goldCount(0) {
    setupScene(); // 设置场景
    level=0;
    // 出怪时间，设置定时器每两秒发射一次信号
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnMonster);
    spawnTimer->start(2000);
    QPixmap cir(":/res_of_qt/circle.jpg");
    circle* c1=new circle(100.0, 150.0, 0, monsters,  cir, scene);
    c1->start_duration(monsters);
    circle* c2=new circle(400.0, 100.0, 0, monsters,  cir, scene);
    c2->start_duration(monsters);
}

MainWindow::~MainWindow() {
    delete scene;
    delete spawnTimer;
}

void MainWindow::setupScene() {
    // 主视图
    scene->setSceneRect(0, 0, 650, 350); // 设置场景大小
    QGraphicsView *view = new QGraphicsView(scene); // 创建图形视图
    setCentralWidget(view);

    // 画个背景
    QPixmap background(":/res_of_qt/background1.png");
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(background);
    backgroundItem->setPos(0, 0);
    backgroundItem->setZValue(-1); // 防止覆盖
    scene->addItem(backgroundItem);


    // 画显示金币
    goldLabel = new QLabel(this);
    goldLabel->setText("金币: " + QString::number(goldCount));
    goldLabel->setStyleSheet("QLabel { font-size: 16px; color: yellow; }");
    goldLabel->setGeometry(view->width() - 120, 10, 100, 30);
    goldLabel->raise(); // 确保在其他组件上方
}

void MainWindow::spawnMonster() {
    // 血量，速度，金币
    Monster *monster = new Monster(1000, 5, 10);

    //这里接到信号了
    connect(monster, &Monster::monsterKilled, this, [this, monster](int gold) {
        goldCount += gold; // 增加金币数
        goldLabel->setText("金币: " + QString::number(goldCount)); // 更新显示
        scene->removeItem(monster);
        monsters.removeAll(monster);
        monster->deleteLater();
    });
    scene->addItem(monster);
    monsters.append(monster);
}
