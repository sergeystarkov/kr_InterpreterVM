#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::loadFile - Загрузка файла
 *
 * Загружает файл программы для предпросмотра программы
 */
void MainWindow::loadFile()
{
    QString text, path;
    path = ui->pathToFile->text();
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        text = file.readAll();
    }
    else {
        QMessageBox m; m.setText("Не удалось открыть файл: " + path); m.exec();
    }
    if(file.isOpen()) file.close();
    ui->programText->setText(text);
}

/**
 * @brief MainWindow::on_startInterpereter_clicked - Кнопка запуска инретпретатора
 *
 * Сохраняет текст программы из редактора во временный файл.
 * Инициализирует поток для интерпретатора.
 * Запскает интерпретатор в отдельном от GUI потоке (в качестве файла программы выступает временный *.tmp файл).
 * По завершении работы интерпретатора удаляет временый файл.
 */
void MainWindow::on_startInterpereter_clicked()
{    
    if(ui->programText->toPlainText().isEmpty()) return;
    QString tmpPath = ui->pathToFile->text() + ".tmp";

    QFile file(tmpPath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QByteArray ba;
        ba.append(ui->programText->toPlainText());
        file.write(ba);
    }
    if(file.isOpen()) file.close();

    //старт интерпретатора в потоке
    VMThread = new QThread();

    Interpreter = new interpreter(tmpPath);
    connect(Interpreter,SIGNAL(destroyed(QObject*)),this,SLOT(stopInterpreter()));
    connect(Interpreter,SIGNAL(debugMSG(QString)),this,SLOT(debugMessage(QString)));

    Interpreter->moveToThread(VMThread);
    VMThread->start();
    Interpreter->startVM();

    QFile(tmpPath).remove();
}

/**
 * @brief MainWindow::stopInterpreter - Завершение работы интерпретатора
 *
 * Остановка потока, высвобождение ресурсов
 */
void MainWindow::stopInterpreter()
{
    VMThread->quit();
    VMThread->wait(100);
    delete VMThread;
}

/**
 * @brief MainWindow::on_save_clicked Сохранить файл
 *
 * Сохраняет файл из текстового редактора
 */
void MainWindow::on_save_clicked()
{
    QString path;
    path = ui->pathToFile->text();
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QByteArray ba;
        ba.append(ui->programText->toPlainText());
        file.write(ba);
    }
    if(file.isOpen()) file.close();
}

/**
 * @brief MainWindow::on_openFile_clicked - форма для выбора файла для открытия
 */
void MainWindow::on_openFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Text (*.txt);");
    ui->pathToFile->setText(path);
    if(!path.isEmpty()) loadFile();
}

/**
 * @brief MainWindow::debugMessage - вывод сообщения на форму
 * @param str - текст сообщения
 */
void MainWindow::debugMessage(QString str)
{
    ui->debugLog->append(str);
}

/**
 * @brief MainWindow::on_SaveAs_clicked - Сохранить как?
 *
 * Открытие формы для указания имени файла для сохраниения
 */
void MainWindow::on_SaveAs_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"),
                                QDir::currentPath(),
                                "Text (*.txt);");
    ui->pathToFile->setText(path);
    on_save_clicked();
}
