#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton* test = new QPushButton("test",this);
    connect(test,&QPushButton::clicked,start_page,&Start::SHOW);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_test_clicked()
{
    start_page->show();
    this->close();
}
