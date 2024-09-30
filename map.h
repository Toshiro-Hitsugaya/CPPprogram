#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QMouseEvent>
#include <QGraphicsItemGroup>
#include <def.h>


// 地图的定义：0表示可以放置炮塔，1表示是路
int map_0[ROW_0][COLUMN_0] = {
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1}
};

// Map类封装地图的绘制和操作
class Map : public QGraphicsItemGroup {
private:
    QGraphicsRectItem* previewRect;  // 预览矩形
public:
    Map() {
        drawMap();
        previewRect = nullptr;
    }

    // 绘制地图网格
    void drawMap() {
        for (int row = 0; row < ROW_0; ++row) {
            for (int col = 0; col < COLUMN_0; ++col) {
                bool isPath = map_0[row][col] == 1;
                QGraphicsRectItem* cell = createCell(row, col, isPath);
                addToGroup(cell);  // 添加到组中
            }
        }
    }

    // 创建单个格子
    QGraphicsRectItem* createCell(int row, int col, bool isPath) {
        QGraphicsRectItem* rect = new QGraphicsRectItem(col * CELL_SIZE_0, row * CELL_SIZE_0, CELL_SIZE_0, CELL_SIZE_0);
        if (isPath) {
            rect->setBrush(QBrush(Qt::gray));  // 用灰色表示路
        } else {
            rect->setBrush(QBrush(Qt::green));  // 用绿色表示可以放炮塔的地方
        }
        rect->setPen(QPen(Qt::black));  // 设置边框颜色
        return rect;
    }

    // 处理鼠标悬停事件，显示预览效果
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        QPointF pos = event->scenePos();
        int col = static_cast<int>(pos.x()) / CELL_SIZE_0;
        int row = static_cast<int>(pos.y()) / CELL_SIZE_0;

        // 确保鼠标位于地图范围内
        if (row >= 0 && row < ROW_0 && col >= 0 && col < COLUMN_0 && map_0[row][col] == 0) {
            showPreview(row, col);
        } else {
            hidePreview();
        }
    }

    // 显示预览
    void showPreview(int row, int col) {
        if (!previewRect) {
            previewRect = new QGraphicsRectItem(col * CELL_SIZE_0, row * CELL_SIZE_0, CELL_SIZE_0, CELL_SIZE_0);
            previewRect->setBrush(QBrush(Qt::yellow, Qt::Dense4Pattern));  // 预览塔位置
            previewRect->setPen(QPen(Qt::DashLine));  // 设置虚线框
            addToGroup(previewRect);
        } else {
            previewRect->setRect(col * CELL_SIZE_0, row * CELL_SIZE_0, CELL_SIZE_0, CELL_SIZE_0);
            previewRect->setVisible(true);
        }
    }

    // 隐藏预览
    void hidePreview() {
        if (previewRect) {
            previewRect->setVisible(false);
        }
    }


};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);

    // 设置背景
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap(":/background.png"));
    scene.addItem(background);

    // 创建Map 添加到场景
    Map* map = new Map();
    scene.addItem(map);

    // 尺寸 显示
    view.setFixedSize(COLUMN_0 * CELL_SIZE_0 + 2, ROW_0 * CELL_SIZE_0 + 2);  // 视图大小
    view.setSceneRect(0, 0, COLUMN_0 * CELL_SIZE_0, ROW_0 * CELL_SIZE_0);     // 场景范围

    view.setMouseTracking(true);
    scene.installEventFilter(map);

    view.show();

    return app.exec();
}
