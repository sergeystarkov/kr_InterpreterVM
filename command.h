#ifndef COMMAND_H
#define COMMAND_H


//Класс реализует выполнение опкодов
class commands
{
public:
    commands(){}
    ~commands(){}

    static int op_1(){return 1;}//реализацию пожже вынести из тела класса, оставить только объявления
    static int op_2(){return 1;}//..
    static int op_3();//..
};



#endif // COMMAND_H

