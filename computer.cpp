#include "computer.h"

Computer::Computer()
{
    Cmd[OP_1] = CMD(new _op_1());
}

Computer::~Computer()
{

}

void Computer::test()
{
   Cmd[OP_1].pOP->operator ()(this);
   QMessageBox b;
   b.setText(QString::number(k));
   b.exec();
}
