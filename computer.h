#ifndef COMPUTER_H
#define COMPUTER_H

#include "operation.h"
#include "types.h"
#include "command.h"

class Computer
{
public:
    Computer();
    ~Computer();

    friend class com;
    struct CMD{
       uByte Length; // длина команды
       int (*pOP)();
       CMD(uByte LEN, int (*FOO)());
       CMD(){}
    };
    CMD Cmd[256]; // основной набор команд
};

#endif // COMPUTER_H
