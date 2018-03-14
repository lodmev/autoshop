#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    db = new DataBase();
    db->connectToDataBase();
    QWidget *centralWidget = new QWidget(this) ;
    this->setCentralWidget(centralWidget);
    this->setWindowTitle("Поиск по базе");
    mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);
    apm = new AllPartsModel();
    proxyModel = new QSortFilterProxyModel();
    m_view = new QTableView;
    m_viewHHeader = m_view->horizontalHeader() ;
    updateButton  = new QPushButton("Обновить данные");
    //m_view->setModel(apm);
   // proxyModel->setSourceModel(apm);
    //QtConcurrent::run(proxyModel,&QSortFilterProxyModel::setSourceModel,apm);
    upLayout = new QHBoxLayout();
    upLayout->addWidget(numSearch  = new QLineEdit());//,0,0,Qt::AlignCenter );
    upLayout->addWidget(nameSearch = new QLineEdit());//,0,1,Qt::AlignCenter );
    upLayout->addWidget(artSearch  = new QLineEdit());//,0,2,Qt::AlignCenter );
    upLayout->addWidget(carSearch  = new QLineEdit());//,0,3,Qt::AlignCenter );
    upLayout->addWidget(clearAllButton = new QPushButton("Очистить"));//,0,4,Qt::AlignCenter );
    upLayout->setSpacing(1);
    numSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    nameSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    artSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    carSearch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    clearAllButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    artSearch->setFocus();
    mainLayout->addWidget(updateButton);
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(m_view);
    clearAllButton->setFixedWidth(70);
    this->setConnections();
    //this->setTableAttribute() ;
    this->setMinimumWidth(750);
    this->resize(900,600);
    emit ready();
}
void MainWindow::allPartsReady()
{
    proxyModel->setSourceModel(apm);
    qDebug() << "update succes!";
    m_view->setModel(proxyModel);
    m_view->setSortingEnabled(true);
    proxyModel->sort(AllPartsModel::NUM,Qt::DescendingOrder);
    this->setTableAttribute() ;
    artSearch->setFocus();
}
void MainWindow::resizeInputFields(int logIndex, int , int newSize) {
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
      clearAllButton->setMaximumWidth(newSize+10);
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
    connect(updateButton,&QPushButton::clicked,this,&MainWindow::makeNewAPModel);
    connect(this,&MainWindow::ready,apm,&AllPartsModel::updateData);
    connect(apm,&AllPartsModel::ready,this,&MainWindow::allPartsReady);
    connect(m_viewHHeader,&QHeaderView::sectionResized,this,&MainWindow::resizeInputFields);
}
void MainWindow::makeNewAPModel(){
    AllPartsModel *alpamo = new AllPartsModel();
    connect(alpamo,&AllPartsModel::readyModel,this,&MainWindow::updateSourceModel);
    connect(this,&MainWindow::setDataToModel,alpamo,&AllPartsModel::updateData);
    emit setDataToModel();
}
void MainWindow::updateSourceModel(AllPartsModel * allPartsM){
    proxyModel->setSourceModel(allPartsM);
    qDebug() << "обновили source model" ;
}
MainWindow::~MainWindow()
{

}



