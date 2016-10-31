#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pathToFile->setText("D:/testProg.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    QString tmpPath;
    tmpPath = ui->pathToFile->text() + ".tmp";
    QMessageBox m; m.setText(tmpPath); m.exec();
    QFile file(tmpPath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QByteArray ba;
        ba.append(ui->programText->toPlainText());
        file.write(ba);
    }
    if(file.isOpen()) file.close();

    VMThread = new QThread(this);
    Interpreter = new interpreter(tmpPath);
    Interpreter->moveToThread(VMThread);
    VMThread->start();
    Interpreter->startVM();
}

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
