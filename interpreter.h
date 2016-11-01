#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>

#include "computer.h"

#include <QStringList>
#include <QLineEdit>
#include <QInputDialog>

#include "operation.h"

//QString execResultCodes[] = {"0 - Программа удачно завершилась",
//                              "1 - Операция успешно выполнена",
//                              "2 - Файл программы не удалось загрузить",
//                              "3 - Значение вышло за пределы адресуемой памяти",
//                              "4 - Переполнение целого числа",
//                              "5 - Переполнение вещественного числа"
//                             };

class interpreter : public QObject
{
    Q_OBJECT
public:
    interpreter(QString PATH);
    Computer *VM;

public slots:
    int startVM();

private:
    friend class Computer;
    static QString inputDialog(QString text);
    static void outputDialog(QString str);
private:
    QString ProgramPath;

};

#endif // INTERPRETER_H
