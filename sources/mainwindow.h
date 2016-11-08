#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtGui>
#include <QFileDialog>

#include "interpreter.h"

/// пространство имён формы QT
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class - GUI форма программы
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    ///Конструктор класса формы QT
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startInterpereter_clicked();    ///< Запуск интерпретатора
    void on_save_clicked();                 ///< Сохранить
    void on_openFile_clicked();             ///< Открыть файл
    void on_SaveAs_clicked();               ///< Сохранить как
    void debugMessage(QString);             ///< Вывод сообщений на форму
    void stopInterpreter();                 ///< Высвобождение ресурсов, закрытие потока

private:
    void loadFile();    ///< Вывод файла в редактор
    QThread *VMThread;          ///< Поток для интерпретатора
    interpreter *Interpreter;   ///< Объект интерпретатора

    Ui::MainWindow *ui; ///<Объект формы QT
};

#endif // MAINWINDOW_H
