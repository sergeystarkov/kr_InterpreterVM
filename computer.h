#ifndef COMPUTER_H
#define COMPUTER_H

#include "operation.h"
#include "types.h"
#include "command.h"

class Command;


class Computer
{
public:
    friend class Command;

    Computer();
    ~Computer();

    struct CMD{
       Command *pOP;                       //Указатель на объект класса с реализацией комманды процессора
       CMD(Command *_pOP) : pOP(_pOP){}    //Конструктор структуры. Параметр - указатель на конкретный класс опкода
       CMD(){}                             //Стандарный конструтор
    };
    CMD Cmd[256];                          //набор команд









    void test(){
        Cmd[OP_1].pOP->operator()();
    }
};

#endif // COMPUTER_H
