#ifndef ALLPARTS_H
#define ALLPARTS_H

#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QGridLayout>
#include "database.h"
#include "mainwindow.h"
class AllParts : public QObject
{
    Q_OBJECT
public:
    explicit AllParts(QObject *parent=0);
    ~AllParts();
signals:
    ready();
public slots:
void reLoadData(QTableWidget *);
private:
    QStringList headers;
    DataBase        *db;

};

#endif // ALLPARTS_H
