#include "map.h"

map::map(int r, int c)
    :max_r(r), max_c(c), showingBlueprint(false) {
    QPixmap background(":/res_of_qt/background1.png");
    QPixmap scaledBackground = background.scaled(600, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(scaledBackground);
    backgroundItem->setPos(0, 0);
    backgroundItem->setZValue(-1); // 防止覆盖
    addItem(backgroundItem);
    QTimer *spawnTimer=new QTimer(); // 定时器
    connect(spawnTimer, &QTimer::timeout, this, &map::spawnMonster);
    spawnTimer->start(2000);

    new circle(100.0, 150.0, FIRE, monsters, this);
    new circle(400.0, 150.0, ICE, monsters, this);




    // 创建蓝图矩形并初始化为不可见
    blueprintItem = new QGraphicsRectItem(0, 0, CELLSIZE, CELLSIZE);
    blueprintItem->setBrush(QColor(0, 0, 255, 127));  // 半透明蓝色
    blueprintItem->setVisible(false);
    addItem(blueprintItem);
}

void map::setMap(const QString & filename) {
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()) {
        int r, c;
        in >> r >> c;
        cell[r][c].canPlace = true;
    }
    file.close();
}

bool map::place(int r, int c, towerBase* tower) {
    if (cell[r][c].canPlace) {
        cell[r][c].tower = tower;
        towers.append(tower);

        // 显示塔的位置
        QGraphicsRectItem* towerItem = new QGraphicsRectItem(c * CELLSIZE, r * CELLSIZE, CELLSIZE, CELLSIZE);
        towerItem->setBrush(Qt::red);
        addItem(towerItem);

        cell[r][c].canPlace = false;
        return true;
    }
    return false;
}

bool map::remove(int r, int c) {
    if (towers.removeOne(cell[r][c].tower)) {
        return true;
    }
    return false;
}

void map::spawnMonster(){
    Monster *monster = new Monster(1000.0, 5.0, 10, this, monsters);
    addItem(monster);
    monster->setZValue(LAYER_MONSTER);
    monsters.append(monster);
}

void map::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_1) {
        showingBlueprint = true;
    }
    QGraphicsScene::keyPressEvent(event);
}

void map::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (showingBlueprint) {
        int r = static_cast<int>(event->scenePos().y()) / CELLSIZE;
        int c = static_cast<int>(event->scenePos().x()) / CELLSIZE;

        // 确保行列索引在地图范围内
        if (r >= 0 && r < max_r && c >= 0 && c < max_c) {
            // 仅当该格子可以放置时显示蓝图
            if (cell[r][c].canPlace) {
                blueprintItem->setPos(c * CELLSIZE, r * CELLSIZE);
                blueprintItem->setVisible(true);
            } else {
                blueprintItem->setVisible(false);
            }
        } else {
            blueprintItem->setVisible(false); // 超出范围隐藏蓝图
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void map::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    int r = static_cast<int>(event->scenePos().y()) / CELLSIZE;
    int c = static_cast<int>(event->scenePos().x()) / CELLSIZE;

    if (showingBlueprint && r >= 0 && r < max_r && c >= 0 && c < max_c && cell[r][c].canPlace) {
        towerBase* tower = new tower1(c * CELLSIZE+CELLSIZE/2, r * CELLSIZE+CELLSIZE/2, monsters, this);
        if (place(r, c, tower)) {
            // 放置塔后，隐藏蓝图
            showingBlueprint = false;
            blueprintItem->setVisible(false);
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
