#ifndef COMPUTER_H
#define COMPUTER_H

#include <QMessageBox>


#include "operation.h"
#include "types.h"
#include "command.h"

class Computer
{
public:

    friend class Command;
    friend class CPU;
    Computer();
    ~Computer();




private:        //Регистры, память и т.п.

    Command *pCMD[256]; //набор команд процессора

    unsigned int SUM;  //Сумматор int 4 байта

    byte *MEM = new byte[0xff];  //оперативная память 1 байтовая

    short AR; //Адресный регистр 2 байта

    union data{
        int I;
        int R;
    };

public:
    void test();
};
#endif // COMPUTER_H
