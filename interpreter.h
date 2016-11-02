#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include <QLineEdit>
#include <QInputDialog>

#include "computer.h"
#include "operation.h"





class interpreter : public QObject
{
    Q_OBJECT
    friend class Computer;
public:
    interpreter(QString PATH) : ProgramPath(PATH){}
    ~interpreter();

    void startVM();         //интерфейс для запуска
signals:
    void debugMSG(QString); //Сигнал для отправки сообщения в поток формы
private:
    Computer *VM;           //Объект компьютер
    static QString inputDialog(QString text);   //диалоговое окно ввод
    static void outputDialog(QString str);      //диалоговое окно вывод
    QString ProgramPath;    //Путь до файла программы
    void debug(QString);    //Лог
};

#endif // INTERPRETER_H
