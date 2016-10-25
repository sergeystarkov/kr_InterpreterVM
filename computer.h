#ifndef COMPUTER_H
#define COMPUTER_H

#include <QMessageBox>


#include "operation.h"
#include "types.h"
#include "command.h"


class Computer
{
public:

    friend class CPUCommand;
    friend class CPU;
    Computer();
    ~Computer();

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
        int R;  //Либо вещественные
    }DATA;

    //PSW (Cостояние процессора)
    struct bits
    {
        unsigned int IP:16; //Instruction Pointer
        unsigned int CF:1; // бит переноса
        unsigned int OF:1; // переполнение знаковое целое
        unsigned int OV:1; // переполнение плавающей арифметики
        unsigned int UV:1; // антипереполнение плавающей арифметики
        unsigned int TF:1; // флаг трассировки
        unsigned int:11; // пока не используется
    }PSW;
#pragma pack(pop)

private:        //Регистры, память и т.п.

    CPUCommand *pCMD[256]; //набор команд процессора

    data        RS;     //Сумматор int 4 байта
    address     RA;     //Адресный регистр 2 байта

    byte *MEM = new byte[0xffff];  //оперативная память 1 байтовая





public:
    void test();
};
#endif // COMPUTER_H
