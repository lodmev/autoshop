#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Поиск по базе");
    AllParts *ap = new AllParts();
    tbl = new QTableWidget(this);
    connect(this,&MainWindow::ready,ap,&AllParts::reLoadData);
    connect(ap,&AllParts::ready,this,&MainWindow::allPartsReady);
    emit ready(tbl);
}
void MainWindow::allPartsReady()
{
  ui->gridLayout->addWidget(tbl);
}

MainWindow::~MainWindow()
{
    delete ui;
}



