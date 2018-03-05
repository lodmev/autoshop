#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Поиск по базе");
    apm = new AllPartsModel();
    proxyModel = new QSortFilterProxyModel(this);
    m_view = new QTableView;
      m_view->setSortingEnabled(true);
      ui->gridLayout->addWidget(m_view);
    connect(this,&MainWindow::ready,apm,&AllPartsModel::updateData);
    connect(apm,&AllPartsModel::ready,this,&MainWindow::allPartsReady);
    emit ready();
}
void MainWindow::allPartsReady()
{
    proxyModel->setSourceModel(apm);
    proxyModel->sort(AllPartsModel::NUM,Qt::DescendingOrder);
    m_view->setModel(proxyModel);
    m_view->setColumnHidden(AllPartsModel::CLIENTID,true);
    m_view->setColumnHidden(AllPartsModel::IDMODEL,true);
    m_view->resizeColumnsToContents();
    m_view->horizontalHeader()->setSectionResizeMode(AllPartsModel::NAME, QHeaderView::Stretch );
}

MainWindow::~MainWindow()
{
    delete ui;
}



