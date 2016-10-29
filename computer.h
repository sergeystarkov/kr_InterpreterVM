#ifndef COMPUTER_H
#define COMPUTER_H

#include <QMessageBox>

#include <QFile>
#include <QStringList>

#include "operation.h"
#include "types.h"
#include "command.h"

#include "assert.h"
class Computer
{
public:

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

    Computer();
    ~Computer();

    void load(QString path);
    void start();


#pragma pack(push,1) //Выравнивание по 1 байту

    //структура команды процессора
    struct command{
        union {
            byte Cmd;               //код операции 1 байт в флагом адресации на старшем бите
            struct{
                unsigned OP:7;      //Код операции
                unsigned B:1;       //Флаг адресации
            };
        };
        union{
            address Addr;               //Адрес аргумента
            struct {
                byte H_Addr;
                byte L_Addr;
            };
        };

    }CMD;

    //Объединение данные
    union data{
        int I;  //Либо целые
        float R;  //Либо вещественные
    }DATA;

    //PSW (Cостояние процессора)
    struct bits
    {
        unsigned int IP;    //Instruction Pointer
        unsigned int SF:1;  //Sign flag результат положительный - 1
        unsigned int ZF:1;  //Zero flag Резульат равен нулю - 1
        unsigned int OF:1;  //Overflow flag переполнение
        unsigned int:13;    //пока не используется
    }PSW;
#pragma pack(pop)

private:        //Регистры, память и т.п.

    Command *pCMD[128]; //набор команд процессора

    data        RS;     //Сумматор 4 байта
    address     RA;     //Адресный регистр 2 байта

    data        R1;     //Внутренний регистр

    byte *MEM = new byte[0xffff];  //оперативная память 1 байтовая

    void flagI();
    void flagR();

    void run();     //Основной цикл процессора

public:
    void test();    //Временная функция для отладки
};
#endif // COMPUTER_H
