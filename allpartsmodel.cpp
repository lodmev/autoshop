#include "allpartsmodel.h"

AllPartsModel::AllPartsModel( QObject* parent ) : QAbstractTableModel( parent ) {

}

int AllPartsModel::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_parts.count();
}

int AllPartsModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return LAST;
}
QVariant AllPartsModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return QVariant();
    }

    switch( section ) {
    case NUM:
        return "Номер чека";
    case NAME:
        return "Наименование" ;
    case ART:
        return "Артикул";
    case CAR:
        return "Автомобиль";
    case PRICE:
        return "Цена за 1шт";
    }
    return QVariant();
}
QVariant AllPartsModel::data( const QModelIndex& index, int role ) const {
    if(
            !index.isValid() ||
            m_parts.count() <= index.row() ||
            ( role != Qt::DisplayRole && role != Qt::EditRole )
        ) {
            return QVariant();
        }

    return m_parts.at(index.row())[ Column( index.column() )];
}

Qt::ItemFlags AllPartsModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        /*if( index.column() == SELECTION ) {
            flags |= Qt::ItemIsEditable;
        } */
    }

    return flags;
}
void AllPartsModel::appendPart( const uint num, const QString& name,
                                const QString& art, const QString& car,
                                const QString& clId, const QString& modId,
                                const QString& price) {
    PartData p_data;
    p_data[NUM]     =num;
    p_data[NAME]    =name;
    p_data[ART]     =art;
    p_data[CAR]     =car;
    p_data[CLIENTID]=clId;
    p_data[IDMODEL] =modId;
    p_data[PRICE]   =price;
    int row = m_parts.count();
    beginInsertRows( QModelIndex(), row, row );
    m_parts.append( p_data );
    endInsertRows();
}
void AllPartsModel::makeQuery(){
    qDebug() << "updating...";
    QSqlQuery query;
    if (!query.exec("select * from GETALLPARTS"))
        qDebug() << "SQL ERROR: " << query.lastError().text();
    while(query.next()){
        this->appendPart(query.value(NUM).toUInt(),query.value(NAME).toString(),query.value(ART).toString(),
                         query.value(CAR).toString(),query.value(CLIENTID).toString(),query.value(IDMODEL).toString(),query.value(PRICE).toString() );
    }
    emit ready();
    emit readyModel(this);
}
void AllPartsModel::updateData(){
   //makeQuery();
    QtConcurrent::run(this,&AllPartsModel::makeQuery);
}

