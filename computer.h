#ifndef COMPUTER_H
#define COMPUTER_H

#include <QMessageBox>
#include <QVector>

#include "operation.h"
#include "types.h"
#include "command.h"

class Computer
{
public:

    friend class Command;
    friend class _op_1;


    Computer();
    ~Computer();

    //Структура команды процесора
    struct CMD{
       Command *pOP;                       //Указатель на объект класса с реализацией комманды процессора
       CMD(Command *_pOP) : pOP(_pOP){}    //Конструктор структуры. Параметр - указатель на конкретный класс опкода
       CMD(){}                             //Стандарный конструтор
    };
    CMD Cmd[256];                          //набор команд


private:        //Регистры, память и т.п.
    int k = 9;

    QVector<CMD>    cmdMemory;
    char            memory[16000];


public:
    void test();
};
#endif // COMPUTER_H
