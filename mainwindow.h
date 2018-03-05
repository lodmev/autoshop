#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSortFilterProxyModel>
#include "allpartsmodel.h"

namespace Ui {
class MainWindow;
}

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
private:
    Ui::MainWindow  *ui;
    QTableView *m_view;
    AllPartsModel *apm;
    QSortFilterProxyModel *proxyModel;
};

#endif // MAINWINDOW_H
