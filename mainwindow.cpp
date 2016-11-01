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

//Загрузка программы и файла
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
}

//Высвобождение ресурсов, закрытие потока
void MainWindow::stopInterpreter()
{
    VMThread->quit();
    VMThread->wait(100);
    delete VMThread;
}

//Сохранение текста программы в файл
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

//Выбор и агрухка файла программы
void MainWindow::on_openFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Text (*.txt);");
    ui->pathToFile->setText(path);
    if(!path.isEmpty()) loadFile();
}

void MainWindow::debugMessage(QString str)
{
    ui->debugLog->append(str);
}
