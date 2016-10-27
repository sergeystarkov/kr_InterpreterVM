#ifndef COMPUTER_H
#define COMPUTER_H

#include <QMessageBox>

#include <QFile>

#include "operation.h"
#include "types.h"
#include "command.h"

#include "assert.h"
class Computer
{
public:

    friend class CPUCommand;
    friend class CPU;
    Computer();
    ~Computer();

    void load(QString path);
    void start();
    void run();

#pragma pack(push,1) //Выравнивание по 1 байту
    //структура команды процессора
    struct command{
        byte code:7;        //Код операции
        byte b:1;           //Флаг адреса b = 0 – адрес (абсолютная адресация)
                            //b = 1 – адрес + регистр (индексная или базовая)
        address addr:16;    //Адрес аргумента
    }CMD;

    //Объединение данные
    union data{
        int I;  //Либо целые
        float R;  //Либо вещественные
    }DATA;

    //PSW (Cостояние процессора)
    struct bits
    {
        unsigned int IP:16; //Instruction Pointer
        unsigned int SF:1;  //Sign flag результат положительный - 1
        unsigned int ZF:1;  //Zero flag Резульат равен нулю - 1
        unsigned int OF:1;  //Overflow flag переполнение
        unsigned int:13;    // пока не используется
    }PSW;
#pragma pack(pop)

private:        //Регистры, память и т.п.

    CPUCommand *pCMD[256]; //набор команд процессора

    data        RS;     //Сумматор 4 байта
    address     RA;     //Адресный регистр 2 байта

    data        R1;     //Внутренний регистр
    data        R2;     //Внутренний регистр

    byte *MEM = new byte[0xffff];  //оперативная память 1 байтовая

    void flagI();
    void flagR();

public:
    void test(); //Временная функция для отладки
};
#endif // COMPUTER_H
