#ifndef TYPES_H
#define TYPES_H

//Типы данных

//typedef signed char Byte;
typedef unsigned char byte;
//typedef unsigned short uShort;
//typedef int Word;
//typedef unsigned int uWord;
//typedef long long Long;
//typedef unsigned long long uLong;
//typedef float Float;
//typedef double Double;

typedef unsigned short address;

struct Registers
{
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
    } PSW;
};









#endif // TYPES_H
