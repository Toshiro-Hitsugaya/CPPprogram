#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <def.h>
#include <circle.h>
#include <map.h>
class MainWindow : public QMainWindow {
public:
    MainWindow(); // 构造
    ~MainWindow(); // 析构
    void spawnMonster(); // 出怪点


private:
    QGraphicsScene *scene;
    void setupScene(); // 设置场景
    QTimer *spawnTimer; // 定时器
    QLabel *goldLabel; // 用于显示金币数
};

#endif
