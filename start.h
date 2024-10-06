#ifndef START_H
#define START_H

#include <QWidget>

namespace Ui {
class Start;
}
class Start : public QWidget
{
    Q_OBJECT
public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
    void paintEvent(QPaintEvent *event); //只用添加这个绘画类函数就可以了
public slots:
    void SHOW();

private:
    Ui::Start *ui;
};

#endif // START_H
