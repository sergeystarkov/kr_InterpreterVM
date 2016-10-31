#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

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

    void on_save_clicked();

private:
    QThread *VMThread;
    interpreter *Interpreter;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
