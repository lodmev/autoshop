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
    upLayout = new QHBoxLayout();
    upLayout->addWidget(numSearch  = new QLineEdit());//,0,0,Qt::AlignCenter );
    upLayout->addWidget(nameSearch = new QLineEdit());//,0,1,Qt::AlignCenter );
    upLayout->addWidget(artSearch  = new QLineEdit());//,0,2,Qt::AlignCenter );
    upLayout->addWidget(carSearch  = new QLineEdit());//,0,3,Qt::AlignCenter );
    upLayout->addWidget(clearAll   = new QPushButton("Очистить"));//,0,4,Qt::AlignCenter );
    upLayout->setSpacing(1);
    numSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    nameSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    artSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    carSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    clearAll->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    artSearch->setFocus();
    m_view = new QTableView;
    m_view->setModel(proxyModel);
    m_viewHHeader = m_view->horizontalHeader() ;
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(m_view);
    this->setConnections();
    this->resize(900,600);
    emit ready();
}
void MainWindow::allPartsReady()
{
    proxyModel->setSourceModel(apm);
    m_view->setSortingEnabled(true);
    proxyModel->sort(AllPartsModel::NUM,Qt::DescendingOrder);
    this->setTableAttribute() ;
    artSearch->setFocus();
}
void MainWindow::resizeInputFields(int logIndex, int oldS , int newSize) {
   //qDebug() << logIndex << oldS << newSize;
    switch (logIndex) {
     case AllPartsModel::NUM :
      numSearch->setMaximumWidth(newSize);
        break;
     case AllPartsModel::NAME :
        nameSearch->setMaximumWidth(newSize-5);
        break;
     case AllPartsModel::ART :
       artSearch->setMaximumWidth(newSize-5);
        break;
     case AllPartsModel::CAR :
       carSearch->setMaximumWidth(newSize-5);
        break;
    case AllPartsModel::PRICE :
      clearAll->setMaximumWidth(newSize);
       break;
    }
}
void MainWindow::setTableAttribute(){
    m_viewHHeader->setSectionResizeMode(AllPartsModel::NAME,QHeaderView::Stretch );
    m_viewHHeader->setSectionHidden(AllPartsModel::CLIENTID,true);
    m_viewHHeader->setSectionHidden(AllPartsModel::IDMODEL,true);
    m_view->resizeColumnsToContents();
}
void MainWindow::setConnections(){
    connect(this,&MainWindow::ready,apm,&AllPartsModel::updateData);
    connect(apm,&AllPartsModel::ready,this,&MainWindow::allPartsReady);
    connect(m_viewHHeader,&QHeaderView::sectionResized,this,&MainWindow::resizeInputFields);
}
MainWindow::~MainWindow()
{

}



