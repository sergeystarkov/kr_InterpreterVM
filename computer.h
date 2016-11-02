#ifndef COMPUTER_H
#define COMPUTER_H

#include <QMessageBox>
#include <QFile>

#include "operation.h"
#include "types.h"
#include "command.h"

class interpreter;

class Computer
{
    //Дружественные классы
    //с реализацией команд
    friend class Command;
    friend class cIadd;
    friend class cRadd;
    friend class cIsub;
    friend class cRsub;
    friend class cImul;
    friend class cRmul;
    friend class cIdiv;
    friend class cRdiv;
    friend class cImod;
    friend class cRadr;
    friend class cLoad;
    friend class cStore;
    friend class cJmp;
    friend class cIcmp;
    friend class cRcmp;
    friend class cJZ;
    friend class cJG;
    friend class cJL;
    friend class cIin;
    friend class cIout;
    friend class cRin;
    friend class cRout;
    //********************

public:
    Computer(QString PATH,interpreter *INTER);
    ~Computer();

    int execute(); //Интерфейс выполнения
private:

    void interrupt(int interruptCode);  //Обработчик прерываний
    interpreter *Interpreter;           //Указатель на объект родитель
    void debug(QString);                //Вывод сообщения в лог
    QString programPath;                //Путь до файла

    void reset();   //сброс регистров
    bool load();    //Загрузка программы
    int run();      //Основной цикл процессора

    void flagI();   //Флаги цел.
    void flagR();   //Флаги вещ.

#pragma pack(push,1) //Выравнивание по 1 байту

    //структура команды процессора
    struct command{
        union {
            byte Cmd;               //код операции 1 байт в флагом адресации на старшем бите
            struct{
                bit OP:7;      //Код операции
                bit B:1;       //Флаг адресации
            };
        };
        union{
            address Addr;       //Адрес аргумента
            struct {
                byte H_Addr;    //Побайтово
                byte L_Addr;    //...
            };
        };
    }CMD;

    //Объединение данные
    union data{
        int I;  //Либо целые
        float R;  //Либо вещественные
        struct { //Побайтовое представление
            byte b1;
            byte b2;
            byte b3;
            byte b4;
        };
    }DATA;

    //PSW (Cостояние процессора)
    struct bits
    {
        address IP; //Instruction Pointer
        bit SF:1;   //Sign flag результат положительный - 1
        bit ZF:1;   //Zero flag Резульат равен нулю - 1
        bit OF:1;   //Overflow flag переполнение
        bit :13;    //не используется
    }PSW;

#pragma pack(pop)

    //Регистры, память и т.п.

    Command *pCMD[128] = {NULL}; //набор команд процессора

    data        RS;     //Сумматор 4 байта
    address     RA;     //Адресный регистр 2 байта
    data        R1;     //Внутренний регистр
    byte *MEM = new byte[0xffff];  //оперативная память 1 байтовая
};

#endif // COMPUTER_H
