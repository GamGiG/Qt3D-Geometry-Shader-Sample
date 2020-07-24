#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Window3D* window = new Window3D();
    ui->verticalLayout->addWidget(QWidget::createWindowContainer(window));
}

MainWindow::~MainWindow()
{
    delete ui;
}
