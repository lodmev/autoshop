#ifndef ALLPARTSMODEL_H
#define ALLPARTSMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QString>
#include <QHash>
#include <QtConcurrent>
//#include <QFuture>
#include "database.h"
class AllPartsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    AllPartsModel(QObject* parent = 0 );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    QVariant data( const QModelIndex& index, int role ) const;
   // bool setData( const QModelIndex& index, const QVariant& value, int role );
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void appendPart(const uint num, const QString& name,
                     const QString& art, const QString& car,
                     const QString& clId, const QString& modId,
                     const QString& price);
    enum Column {
        NUM = 0,
        NAME,
        ART,
        CAR,
        CLIENTID,
        IDMODEL,
        PRICE,
        LAST
    };
    Q_ENUM(Column);
public slots:
void updateData();
signals:
ready();
readyModel(AllPartsModel *);
private:
    void makeQuery();
    typedef QHash< Column, QVariant > PartData;
    typedef QList< PartData > Parts;
    Parts m_parts;
};

#endif // ALLPARTSMODEL_H
