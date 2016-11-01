#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>

#include "computer.h"
#include "operation.h"

#include <QStringList>
#include <QLineEdit>
#include <QInputDialog>

class interpreter : public QObject
{
    Q_OBJECT
    friend class Computer;
public:
    interpreter(QString PATH);
    ~interpreter();
    Computer *VM;
void debug(QString);
public slots:
    void startVM();
signals:
    void debugMSG(QString);
private:
    static QString inputDialog(QString text);
    static void outputDialog(QString str);
    QString ProgramPath;
};

#endif // INTERPRETER_H
