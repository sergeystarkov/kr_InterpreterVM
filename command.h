#ifndef COMMAND_H
#define COMMAND_H

class Computer;
#include <QMessageBox>

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
    Command(){}
    ~Command(){}
    virtual int operator()() const = 0;   //Перегрузка оператора ()
protected:
    CPUCommands *cmd;
};

class _op_1 : public Command
{
public:
    int operator()() const
    {

        //cmd->op_1();
        return 1;
    }
};


#endif // COMMAND_H

