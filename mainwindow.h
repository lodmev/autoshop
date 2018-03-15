#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QSize>
#include "allpartsmodel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
ready();
setDataToModel();
public slots:
void allPartsReady() ;
void changeSourceModel() ;
void resizeInputFields(int,int,int) ;
void setSourceModel(AllPartsModel *);
private:
    QVBoxLayout *mainLayout ;
    QHBoxLayout *upLayout ;
    QTableView *m_view;
    QHeaderView *m_viewHHeader;
    AllPartsModel *apmOne, *apmTwo;
    QSortFilterProxyModel *proxyModel;
    DataBase *db;
    QPushButton *clearAllButton, *updateButton;
    QLineEdit *numSearch, *nameSearch, *artSearch, *carSearch;
    void setTableAttribute();
    void setConnections();
};

#endif // MAINWINDOW_H
