#include "computer.h"

Computer::Computer()
{
    Cmd[OP_1] = CMD(new _op_1());
}

Computer::~Computer()
{

}
