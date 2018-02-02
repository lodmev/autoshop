#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "allparts.h"

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
ready(QTableWidget *);
public slots:
void allPartsReady() ;
private:
    Ui::MainWindow  *ui;
    QTableWidget *tbl;

};

#endif // MAINWINDOW_H
