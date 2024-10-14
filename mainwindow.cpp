#include "mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <Qstring>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow():scene(new map(6, 10)), spawnTimer(new QTimer()) {
    setupScene(); // 设置场景
}

MainWindow::~MainWindow() {
    delete scene;
    delete spawnTimer;
}

void MainWindow::setupScene() {
    // 主视图
    // 设置场景大小和窗口大小  650*350
    const int sceneWidth = 600; // 新场景宽度
    const int sceneHeight = 300; // 新场景高度
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight); // 设置场景大小
    QGraphicsView *view = new QGraphicsView(scene); // 创建图形视图
    view->setMouseTracking(true);
    setCentralWidget(view);

    // 画显示金币
    goldLabel = new QLabel(this);
    goldLabel->setText("金币: " + QString::number(goldCount));
    goldLabel->setStyleSheet("QLabel { font-size: 16px; color: yellow; }");
    goldLabel->setGeometry(view->width() - 120, 10, 100, 30);
    goldLabel->raise(); // 确保在其他组件上方

}
