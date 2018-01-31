#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Поиск по базе");
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

     this->createUI(QStringList() << trUtf8("Номер чека")
                                  << trUtf8("Наименование")
                                  << trUtf8("Артикул")
                                  << trUtf8("Автомобиль")
                                  << trUtf8("CLIENTID")
                                  << trUtf8("IDMODEL")
                                  << trUtf8("Цена")
                    );
    this->showData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI(const QStringList &headers)
{
ui->tableWidget->setColumnCount(7); // Указываем число колонок
   ui->tableWidget->setShowGrid(true); // Включаем сетку
   // Разрешаем выделение только одного элемента
   ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
   // Разрешаем выделение построчно
   ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
   // Устанавливаем заголовки колонок
   ui->tableWidget->setHorizontalHeaderLabels(headers);
   // Растягиваем последнюю колонку на всё доступное пространство
   ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
   // Скрываем колонку под номером 0
   ui->tableWidget->hideColumn(4);
   ui->tableWidget->hideColumn(5);

}
void MainWindow::showData()
{
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
        ui->tableWidget->insertRow(i);
        /* Устанавливаем в первую колонку id забирая его из результата SQL-запроса
         * Эта колонка будет скрыта
         * */
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(query.value(0).toString()));

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
        //ui->tableWidget->setItem(i,1, item);
        // Далее забираем все данные из результата запроса и устанавливаем в остальные поля
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(i,6, new QTableWidgetItem(query.value(4).toString()));
        if (!query.isActive())
        QMessageBox::warning(this, tr("Database Error"),
                                query.lastError().text());
    }


    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}
