#include "MainWindow.h"
#include "Monster.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <Qstring>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), spawnTimer(new QTimer(this)),goldCount(0) {
    setupScene(); // 设置场景

    // 出怪时间，设置定时器每两秒发射一次信号
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnMonster);
    spawnTimer->start(2000);
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
    Monster *monster = new Monster(100, 5, 10);

    //这里接到信号了
    connect(monster, &Monster::monsterKilled, this, [this](int gold) {
        goldCount += gold; // 增加金币数
        goldLabel->setText("金币: " + QString::number(goldCount)); // 更新显示
    });
    scene->addItem(monster);
}

// void MainWindow::paintEvent(QPaintEvent *event) {
//     QMainWindow::paintEvent(event);
//     QPainter painter(this);
//     QPixmap background(":/res_of_qt/background1.png");
//     painter.drawPixmap(0, 0, width(), height(), background);
// }

// void MainWindow::paintEvent(QPaintEvent*)
// {
//     QPainter painter(this);
//     QPixmap pix;
//     pix.load(":/res_of_qt/background1.png");
//     painter.drawPixmap(0, 0, this->width(), this->height(), pix);
// }
