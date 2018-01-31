#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QMessageBox>
/* Подключаем заголовочный файл для работы с информацией, которая помещена в базу данных */
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    /* В проекте используются объекты для взаимодействия с информацией в базе данных
     * и моделью представления таблицы базы данных
     * */
    DataBase        *db;
    QSqlTableModel  *model;

private:
    void createUI(const QStringList &headers);
    void showData();
};

#endif // MAINWINDOW_H
