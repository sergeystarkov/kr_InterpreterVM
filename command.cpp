#include "command.h"




int CPU::STOP(Computer * COMP)
{
    return 1;
}

int CPU::IADD(Computer *COMP)
{
    //COMP->R1 = C
    return 1;
}

int CPU::ISUB(Computer *COMP)
{
    return 1;
}

int CPU::IMUL(Computer *COMP)
{
    return 1;
}

int CPU::IDIV(Computer *COMP)
{
    return 1;
}

int CPU::IMOD(Computer *COMP)
{
    return 1;
}

//Загрузка сумматора из ОЗУ
int CPU::LOAD(Computer *COMP)
{
    if(COMP->CMD.b == 0){
        memcpy( &COMP->RS.I , &COMP->MEM[COMP->CMD.addr] , 4 );
    }else{
        memcpy( &COMP->RS.I , &COMP->MEM[ COMP->RA + COMP->CMD.addr ] , 4 );
    }
    COMP->PSW.IP++; //Переход на сл команду
    return 1;
}

//Выгрузка сумматора в ОЗУ
int CPU::STORE(Computer *COMP)
{
    if(COMP->CMD.b == 0){
        memcpy( &COMP->MEM[COMP->CMD.addr] , &COMP->RS.I , 4 );
    }else{
        memcpy( &COMP->MEM[ COMP->RA + COMP->CMD.addr ] , &COMP->RS.I , 4 );
    }
    COMP->PSW.IP++; //Переход на сл команду
    return 1;
}
