#ifndef COMMAND_H
#define COMMAND_H

#include "computer.h"


class CPUCommands;
class Command;
class _op_1;

//Класс реализует выполнение опкодов
class CPUCommands
{
public:
    CPUCommands(){}
    ~CPUCommands(){}

    static int op_1(){return 1;}//реализацию пожже вынести из тела класса, оставить только объявления
    static int op_2(){return 1;}//..
    static int op_3(){return 1;}//..
};


//Базовый абстрактный класс для паттерна "Комманда"
class Command
{
public:
    friend class Computer;
    virtual int operator()(Computer *) const = 0;   //Перегрузка оператора ()
protected:
    CPUCommands *cmd;
};

class _op_1 : public Command
{
public:
    friend class Computer;
    int operator()(Computer *VM) const;
};

#endif // COMMAND_H



