#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this) ;
    this->setCentralWidget(centralWidget);
    this->setWindowTitle("Поиск по базе");
    mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);
    apm = new AllPartsModel();
    proxyModel = new QSortFilterProxyModel(this);
    upLayout = new QGridLayout;
    upLayout->addWidget(numSearch  = new QLineEdit(),0,0,Qt::AlignCenter );
    upLayout->addWidget(nameSearch = new QLineEdit(),0,1,Qt::AlignCenter );
    upLayout->addWidget(artSearch  = new QLineEdit(),0,2,Qt::AlignCenter );
    upLayout->addWidget(carSearch  = new QLineEdit(),0,3,Qt::AlignCenter );
    upLayout->addWidget(clearAll   = new QPushButton("Очистить"),0,4,Qt::AlignCenter );
    m_view = new QTableView;
    m_view->setModel(apm);
    m_viewHHeader = m_view->horizontalHeader() ;
    this->setTableAttribute() ;
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(m_view);
    connect(this,&MainWindow::ready,apm,&AllPartsModel::updateData);
    connect(apm,&AllPartsModel::ready,this,&MainWindow::allPartsReady);
    connect(m_viewHHeader,&QHeaderView::sectionResized,this,&MainWindow::resizeInputFields);
    this->resize(950,600);
    emit ready();
}
void MainWindow::allPartsReady()
{
    proxyModel->setSourceModel(apm);
    m_view->setModel(proxyModel);
     this->setTableAttribute() ;
    m_view->setSortingEnabled(true);
    proxyModel->sort(AllPartsModel::NUM,Qt::DescendingOrder);
}
void MainWindow::resizeInputFields(int logIndex, int , int newSize) {
    switch (logIndex) {
     case AllPartsModel::NUM :
        numSearch->setMaximumWidth(newSize);
        break;
     case AllPartsModel::NAME :
        nameSearch->setMaximumWidth(newSize);
        break;
     case AllPartsModel::ART :
        artSearch->setMaximumWidth(newSize);
        break;
     case AllPartsModel::CAR :
        carSearch->setMaximumWidth(newSize);
        break;
    case AllPartsModel::PRICE :
       clearAll->setMaximumWidth(newSize);
       break;
    }
}
void MainWindow::setTableAttribute(){
    m_viewHHeader->setSectionResizeMode(QHeaderView::Stretch );
    m_viewHHeader->setSectionHidden(AllPartsModel::CLIENTID,true);
    m_viewHHeader->setSectionHidden(AllPartsModel::IDMODEL,true);
    m_view->resizeColumnsToContents();
}
MainWindow::~MainWindow()
{

}



