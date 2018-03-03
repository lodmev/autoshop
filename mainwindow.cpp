#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Поиск по базе");
    AllPartsModel *apm;
    m_view = new QTableView;
        m_view->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
        m_view->setModel(apm = new AllPartsModel());
        m_view->setColumnHidden(AllPartsModel::CLIENTID,true);
        m_view->setColumnHidden(AllPartsModel::IDMODEL,true);
        m_view->setSortingEnabled(true);
       // m_view->resizeColumnsToContents();
    ui->gridLayout->addWidget(m_view);
    connect(this,&MainWindow::ready,apm,&AllPartsModel::updateData);
    connect(apm,&AllPartsModel::ready,this,&MainWindow::allPartsReady);
    emit ready();
}
void MainWindow::allPartsReady()
{
    m_view->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}



