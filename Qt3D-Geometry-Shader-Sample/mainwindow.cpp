#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window = new Window3D();
    ui->verticalLayout->addWidget(QWidget::createWindowContainer(window));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    for (int i = 0; i < 100; i++) {
        QVector2D center = CustomWalls::generateRandomVector2D();
        QVector2D wh = CustomWalls::generateRandomVector2D(0.5f) + QVector2D(0.6f, 0.6f);
        float h = CustomWalls::generateRandomFloat(5.0f);

        CustomWall* customWall0 = new CustomWall(QVector2D(center.x() - wh.x(), center.y() - wh.y()), QVector2D(center.x() - wh.x(), center.y() + wh.y()), h, window->customWalls);
        CustomWall* customWall1 = new CustomWall(QVector2D(center.x() - wh.x(), center.y() + wh.y()), QVector2D(center.x() + wh.x(), center.y() + wh.y()), h, window->customWalls);
        CustomWall* customWall2 = new CustomWall(QVector2D(center.x() + wh.x(), center.y() + wh.y()), QVector2D(center.x() + wh.x(), center.y() - wh.y()), h, window->customWalls);
        CustomWall* customWall3 = new CustomWall(QVector2D(center.x() + wh.x(), center.y() - wh.y()), QVector2D(center.x() - wh.x(), center.y() - wh.y()), h, window->customWalls);

        QList<CustomWall* > walls;
        walls.append(customWall0);
        walls.append(customWall1);
        walls.append(customWall2);
        walls.append(customWall3);
        window->customWalls->AddWalls(walls);

    }
}
