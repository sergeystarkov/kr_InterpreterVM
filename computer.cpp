#include "computer.h"


Computer::CMD::CMD(uByte LEN, int (*FOO)())
{
    Length = LEN;
    pOP = FOO;
}

Computer::Computer()
{
    Cmd[OP_1] = CMD(2,commands::op_1);

}

Computer::~Computer()
{

}
