#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rotatorwidget.h"
#include "dopplerentity.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->mainLayout->addWidget(new RotatorWidget(new DopplerEntity() ,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

