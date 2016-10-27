#ifndef COMMAND_H
#define COMMAND_H

#include "computer.h"


class CPU;
class CPUCommand;
class Computer;

//Класс процессора реализует выполнение опкодов
class CPU
{
public:
    CPU(){}
    ~CPU(){}
private:
    friend class cSTOP;
    static int STOP(Computer *);

    //Целая арифметика
    friend class cIadd;
    static int IADD(Computer *);

    friend class cIsub;
    static int ISUB(Computer *);

    friend class cImul;
    static int IMUL(Computer *);

    friend class cIdiv;
    static int IDIV(Computer *);

    friend class cImod;
    static int IMOD(Computer *);

    //Дровная арифметика
    friend class cRadd;
    static int RADD(Computer *);

    friend class cRsub;
    static int RSUB(Computer *);

    friend class cRmul;
    static int RMUL(Computer *);

    friend class cRdiv;
    static int RDIV(Computer *);

    //Операции с сумматором
    friend class cLoad;
    static int LOAD(Computer *);

    friend class cStore;
    static int STORE(Computer *);

    //Адресный регистр
    friend class cRadr;
    static int RADR(Computer *);

    //Переходы
    friend class cJmp;
    static int JMP(Computer *);
};




//Базовый абстрактный класс для паттерна "Комманда"
class CPUCommand
{
public:
    virtual int operator()(Computer *) = 0;   //Перегрузка оператора ()
protected:
    CPU cmd;
};
/////////////////////////////////////////////////////

//Объявление  комманд процессора*********************

//СТОП
class cSTOP : public CPUCommand {
public:
    int operator()(Computer *){
       return 0;
    }
};

//Сложение целых чисел
class cIadd : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.IADD(COMP);
       return 1;
    }
};

//Вычитание целых чисел
class cIsub : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.ISUB(COMP);
       return 1;
    }
};

//Умножение целых чисел
class cImul : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.IMUL(COMP);
       return 1;
    }
};

//Деление целых чисел
class cIdiv : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.IDIV(COMP);
       return 1;
    }
};

//Остаток от деления целых чисел
class cImod : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.IMOD(COMP);
       return 1;
    }
};

//Сложение дробных чисел
class cRadd : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.RADD(COMP);
       return 1;
    }
};

//Вычитание дробных чисел
class cRsub : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.RSUB(COMP);
       return 1;
    }
};

//Умножение дробных чисел
class cRmul : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.RMUL(COMP);
       return 1;
    }
};

//Деление дробных чисел
class cRdiv : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.RDIV(COMP);
       return 1;
    }
};

//Загрузка сумматора
class cLoad : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.LOAD(COMP);
       return 1;
    }
};

//Выгрузка сумматора
class cStore : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.STORE(COMP);
       return 1;
    }
};

//Загрузка адрессного регистра
class cRadr : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.RADR(COMP);
       return 1;
    }
};

//Безусловный переход
class cJmp : public CPUCommand {
public:
    int operator()(Computer *COMP){
       cmd.JMP(COMP);
       return 1;
    }
};
#endif // COMMAND_H



