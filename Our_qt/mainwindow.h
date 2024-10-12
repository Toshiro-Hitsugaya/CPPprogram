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
    void removeMonster(Monster* monster);

    bool canPlaceTower(int x, int y);
    void placeTower(int x, int y);
    void startTowerAttack();
    void towerAttack();
    QVector<Monster*> getMonstersInRange(tower1* tower);
    bool isInRange(tower1* tower, Monster* monster);


protected:
    // void paintEvent(QPaintEvent *event) override; // 本来想画背景图的，不用了
    void mousePressEvent(QMouseEvent *event) override;

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
