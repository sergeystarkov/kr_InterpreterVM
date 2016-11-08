#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include <QLineEdit>
#include <QInputDialog>

#include "computer.h"
#include "operation.h"

/**
 * @brief The interpreter class
 *
 * Запускает виртуальную машину, посредник между GUI и ВМ
 */
class interpreter : public QObject
{
    Q_OBJECT
    friend class Computer;
public:
    /**
     * @brief interpreter - Конструктор класса
     * @param PATH - Путь до временного файла программы для запуска
     */
    interpreter(QString PATH) : ProgramPath(PATH){}
    ~interpreter();

    ///Интерфейс запуска интерпретатора
    void startVM();
signals:
    ///Сигнал для отправки сообщения в поток GUI
    void debugMSG(QString);
private:
    Computer *VM;           ///< Объект компьютер
    QString inputDialog(QString text);   ///< диалоговое окно ввод
    void outputDialog(QString str);      ///< диалоговое окно вывод
    QString ProgramPath;    ///< Путь до файла программы
    void debug(QString);    ///< Отправка сигнала с текстом сообщения в поток GUI
};

#endif // INTERPRETER_H
