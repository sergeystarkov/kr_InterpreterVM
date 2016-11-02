#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtGui>
#include <QFileDialog>

#include "interpreter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadFile();    //Вывод файла в редактор

private slots:
    void on_startInterpereter_clicked();    //Запуск интерпретатора
    void on_save_clicked();                 //Сохранить
    void on_openFile_clicked();             //Открыть файл
    void on_SaveAs_clicked();               //Сохранить как
    void debugMessage(QString);             //Вывод лога
    void stopInterpreter();                 //Высвобождение ресурсов, закрытие потока

private:
    QThread *VMThread;          //Поток для интерпретатора
    interpreter *Interpreter;   //Объект интерпретатора

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
