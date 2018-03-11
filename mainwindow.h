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
public slots:
void allPartsReady() ;
void resizeInputFields(int,int,int) ;
private:
    QVBoxLayout *mainLayout ;
    QGridLayout *upLayout ;
    QTableView *m_view;
    QHeaderView *m_viewHHeader;
    AllPartsModel *apm;
    QSortFilterProxyModel *proxyModel;
    QPushButton *clearAll;
    QLineEdit *numSearch, *nameSearch, *artSearch, *carSearch;
    void setTableAttribute();
};

#endif // MAINWINDOW_H
