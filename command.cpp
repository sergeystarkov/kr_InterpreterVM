#include "command.h"

int _op_1::operator()(Computer *VM) const
{
    --VM->k;
    return 1;
}
