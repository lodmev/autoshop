#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
int main(int argc, char *argv[])
{
   // QStringList paths = QCoreApplication::libraryPaths();
       // paths.append("./plugins/platforms");
       // paths.append("./plugins/sqldrivers");
        //QCoreApplication::setLibraryPaths(paths);
    try {
    QApplication a(argc, argv);
    //qDebug() << a.libraryPaths();
    MainWindow w;
    w.show();
    return a.exec();
     }
        catch(std::exception &e)
           {
              QMessageBox::critical(nullptr, "Error", e.what(), QMessageBox::Ok);
              QApplication::exit();
           }
        catch(...)
               {
              QMessageBox::critical(nullptr, "Error", "Unknown exception", QMessageBox::Ok);
              QApplication::exit();
               }
}
