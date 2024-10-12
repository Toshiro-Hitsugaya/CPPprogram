#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsItem>
#include "monster.h"
#include "tower1.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // 构造
    ~MainWindow(); // 析构
    void spawnMonster(); // 出怪点
    void removeMonster(Monster* monster); // 主要是为了移除出怪物列表

    bool canPlaceTower(int x, int y); // 判断是否可以放置塔
    void placeTower(int x, int y); // 放置塔
    void startTowerAttack(); // 开始塔的攻击
    QVector<Monster*> getMonstersInRange(tower1* tower); // 获取塔攻击范围内的怪物
    bool isInRange(tower1* tower, Monster* monster); // 判断怪处在塔的范围

protected:
    void mousePressEvent(QMouseEvent *event) override;  // 鼠标事件

private:
    QGraphicsScene *scene;
    QVector<Monster*> allMonsters; // 怪物列表
    QVector<tower1*> towers; // 塔列表
    void setupScene(); // 设置场景
    QTimer *spawnTimer; // 定时器
    QLabel *goldLabel; // 用于显示金币数
    int goldCount; // 当前金币数
};

#endif
