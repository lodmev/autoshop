#include "allparts.h"

AllParts::AllParts(QObject *parent) : QObject(parent)
{
}
AllParts::~AllParts()
{
}
void AllParts::reLoadData(QTableWidget *tbl)
{
    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();
    /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в TableView
     * */
    /*for(int i = 0; i < 4; i++){
        QVariantList data;
        int random = qrand(); // Получаем случайные целые числа для вставки а базу данных
        data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
        data.append(QTime::currentTime()); // Получаем текущее время для вставки в БД
        // Подготавливаем полученное случайное число для вставки в БД
        data.append(random);
        // Подготавливаем сообщение для вставки в базу данных
        data.append("Получено сообщение от " + QString::number(random));
        // Вставляем данные в БД
        db->inserIntoTable(data);
    } */

     headers = (QStringList() << "Номер чека"
                              << "Наименование"
                              << "Артикул"
                              << "Автомобиль"
                              << "CLIENTID"                                      << "IDMODEL"
                              << "Цена"
                );
        tbl->setColumnCount(7); // Указываем число колонок
        tbl->setSortingEnabled(true); //Активируем сортировку
        // Растягивающаяся вторая колонка
                tbl->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
        tbl->verticalHeader()->setVisible(false);
        tbl->setShowGrid(true); // Включаем сетку
        // Разрешаем выделение только одного элемента
        tbl->setSelectionMode(QAbstractItemView::SingleSelection);
        // Разрешаем выделение построчно
        tbl->setSelectionBehavior(QAbstractItemView::SelectRows);
        // Устанавливаем заголовки колонок
        tbl->setHorizontalHeaderLabels(headers);
        // Скрываем колонку под номером 0
        tbl->hideColumn(4);
        tbl->hideColumn(5);
        // Создаём запрос для для выборки записей из базы данных
        QSqlQuery query;
        //query.setForwardOnly(true);
        /* Выполняем заполнение QTableWidget записями с помощью цикла
        * */
        if (!query.exec("select * from GETALLPARTS"))
         qDebug() << "SQL ERROR: " << query.lastError().text();
        //unsigned recCount = query.record().count();
        //qDebug() << query.numRowsAffected();
        //int i=0;
        while(query.next()){
            int i = query.at();
            //qDebug() << i;
            tbl->insertRow(i);
            /* Устанавливаем в первую колонку id забирая его из результата SQL-запроса
             * Эта колонка будет скрыта
             * */
            tbl->setItem(i,0, new QTableWidgetItem(query.value(0).toString()));

            // Создаём элемент, который будет выполнять роль чекбокса
            /*QTableWidgetItem *item = new QTableWidgetItem();
            item->data(Qt::CheckStateRole); */
            /* Проверяем, на статус нечетности, если нечетное устройство, то
             * выставляем состояние чекбокса в Checked, иначе в Unchecked
             * */
            /*if(query.value(1).toInt() == 1){
                item->setCheckState(Qt::Checked);
            } else {
                item->setCheckState(Qt::Unchecked);
            } */
            // Устанавливаем чекбокс во вторую колонку
            //tbl->setItem(i,1, item);
            // Далее забираем все данные из результата запроса и устанавливаем в остальные поля
            tbl->setItem(i,1, new QTableWidgetItem(query.value(1).toString()));
            tbl->setItem(i,2, new QTableWidgetItem(query.value(2).toString()));
            tbl->setItem(i,3, new QTableWidgetItem(query.value(3).toString()));
            tbl->setItem(i,4, new QTableWidgetItem(query.value(4).toString()));
            tbl->setItem(i,5, new QTableWidgetItem(query.value(5).toString()));
            tbl->setItem(i,6, new QTableWidgetItem(query.value(6).toString()));
            if (!query.isActive())
            QMessageBox::warning(tbl, tr("Database Error"),
                                    query.lastError().text());
        }


        // Ресайзим колонки по содержимому
        tbl->resizeColumnsToContents();
      emit ready();
}


