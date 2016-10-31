#include "interpreter.h"

interpreter::interpreter(QString PATH)
{
    ProgramPath = PATH;
}

int interpreter::startVM()
{
     VM = new Computer(ProgramPath);
     int result = VM->execute();
     delete VM;
     return result;
}

