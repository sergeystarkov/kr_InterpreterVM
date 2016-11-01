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

    void loadFile();

private slots:
    void on_startInterpereter_clicked();
    void stopInterpreter();

    void on_save_clicked();

    void on_openFile_clicked();

    void debugMessage(QString);

private:
    QThread *VMThread;
    interpreter *Interpreter;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
