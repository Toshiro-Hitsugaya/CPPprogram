#ifndef MAP_H
#define MAP_H
#include <def.h>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <circle.h>
#include <monster.h>
#include <towerbase.h>
#include <tower1.h>
class cell {
private:
    friend class map;
    bool canPlace;
    towerBase* tower;
public:
    cell() : canPlace(true), tower(nullptr) {}
};

class map : public QGraphicsScene {
    Q_OBJECT

public:
    map(int r, int c);
    void setMap(const QString & filename);
    bool place(int r, int c, towerBase* tower);
    bool remove(int r, int c);
    void spawnMonster();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int max_r, max_c;
    cell cell[MAX_R][MAX_C];
    QList<Monster*> monsters;
    QVector<towerBase*> towers;

    bool showingBlueprint;
    QGraphicsRectItem* blueprintItem;
};

#endif
