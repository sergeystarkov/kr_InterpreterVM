#ifndef COMMAND_H
#define COMMAND_H


#include "operation.h"

class Computer;

///Базовый абстрактный класс для паттерна "Комманда"
class Command
{
public:
    virtual int operator()(Computer *) = 0;   ///<Перегрузка оператора ()
    virtual ~Command(){}
protected:
    void loadRegister(Computer *COMP);
};


///СТОП
class cSTOP : public Command {
public:
    int operator()(Computer *);
};

///Сложение целых чисел
class cIadd : public Command {
public:
    friend class Computer;
    int operator()(Computer *COMP);
};

///Вычитание целых чисел
class cIsub : public Command {
public:
    int operator()(Computer *COMP);
};

///Умножение целых чисел
class cImul : public Command {
public:
    int operator()(Computer *COMP);
};

///Деление целых чисел
class cIdiv : public Command {
public:
    int operator()(Computer *COMP);
};

///Остаток от деления целых чисел
class cImod : public Command {
public:
    int operator()(Computer *COMP);
};

///Сложение дробных чисел
class cRadd : public Command {
public:
    int operator()(Computer *COMP);
};

///Вычитание дробных чисел
class cRsub : public Command {
public:
    int operator()(Computer *COMP);
};

///Умножение дробных чисел
class cRmul : public Command {
public:
    int operator()(Computer *COMP);
};

///Деление дробных чисел
class cRdiv : public Command {
public:
    int operator()(Computer *COMP);
};

///Загрузка сумматора
class cLoad : public Command {
public:
    int operator()(Computer *COMP);
};

///Выгрузка сумматора
class cStore : public Command {
public:
    int operator()(Computer *COMP);
};

///Загрузка адрессного регистра
class cRadr : public Command {
public:
    int operator()(Computer *COMP);
};

///Сравнение целых
class cIcmp : public Command {
public:
    int operator()(Computer *COMP);
};

///Сравнение вещественных
class cRcmp : public Command {
public:
    int operator()(Computer *COMP);
};

///Безусловный переход
class cJmp : public Command {
public:
    int operator()(Computer *COMP);
};

///переход, если ноль (равны)
class cJZ : public Command {
public:
    int operator()(Computer *COMP);
};

///переход, если больше
class cJG : public Command {
public:
    int operator()(Computer *COMP);
};

///переход, если меньше
class cJL : public Command {
public:
    int operator()(Computer *COMP);
};

///Ввод целого
class cIin : public Command {
public:
    int operator()(Computer *COMP);
};

///Ввод вещественного
class cRin : public Command {
public:
    int operator()(Computer *COMP);
};

///вывод целого
class cIout : public Command {
public:
    int operator()(Computer *COMP);
};

///Вывод вещественного
class cRout : public Command {
public:
    int operator()(Computer *COMP);
};







#endif // COMMAND_H



