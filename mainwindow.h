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
void makeNewAPModel() ;
void resizeInputFields(int,int,int) ;
void updateSourceModel(AllPartsModel *);
private:
    QVBoxLayout *mainLayout ;
    QHBoxLayout *upLayout ;
    QTableView *m_view;
    QHeaderView *m_viewHHeader;
    AllPartsModel *apm;
    QSortFilterProxyModel *proxyModel;
    DataBase *db;
    QPushButton *clearAllButton, *updateButton;
    QLineEdit *numSearch, *nameSearch, *artSearch, *carSearch;
    void setTableAttribute();
    void setConnections();
};

#endif // MAINWINDOW_H
