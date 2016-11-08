#ifndef COMPUTER_H
#define COMPUTER_H

#include <QMessageBox>
#include <QFile>

#include "operation.h"
#include "types.h"
#include "command.h"

class interpreter;
class Command;


/**
 * @brief Класс Computer реализует архитектуру компьютера
 *
 * Содержит в себе реализацию регистров, памяти, и т.д.
 */
class Computer
{
    //Дружественные классы
    //с реализацией команд
    friend class Command;
    friend class cIadd;
    friend class cRadd;
    friend class cIsub;
    friend class cRsub;
    friend class cImul;
    friend class cRmul;
    friend class cIdiv;
    friend class cRdiv;
    friend class cImod;
    friend class cRadr;
    friend class cLoad;
    friend class cStore;
    friend class cJmp;
    friend class cIcmp;
    friend class cRcmp;
    friend class cJZ;
    friend class cJG;
    friend class cJL;
    friend class cIin;
    friend class cIout;
    friend class cRin;
    friend class cRout;
    //********************

public:
    Computer(QString PATH,interpreter *INTER);
    ~Computer();

    ///Запуск выполнения программы
    int execute(); //Интерфейс выполнения
private:

    /**
     * @brief Interpreter - Указатель на родителя
     *
     * Указатель на объект родитель, передающийся классу в качестве параметра.
     * Используется для доступа к членам класса interprerer
     */
    interpreter *Interpreter;

    /**
     * @brief programPath - Путь до файла с программой, которую нужно выполнить
     */
    QString programPath;

    ///Обработчик прерываний
    void interrupt(int interruptCode);

    ///Передача сообщения для последующего вывода в лог
    void debug(QString);

    ///сброс регистров
    void reset();

    ///Загрузка программы
    bool load();

    ///Основной цикл процессора
    int run();

    ///Установка флагов для целого числа
    void flagI();

    ///Установка флагов для вещественного числа
    void flagR();

#pragma pack(push,1) //Выравнивание по 1 байту

    /**
     * @brief command struct - структура команды для выполнения. 3 байта.
     *
     * Структура команды процессора. 3 байта.
     */
    struct command{
        union {
            byte Cmd;       ///< код операции 1 байт в флагом адресации на старшем бите
            struct{
                bit OP:7;   ///< Код операции
                bit B:1;    ///< Флаг адресации
            };
        };
        union{
            address Addr;   ///< Адрес аргумента
            struct {
                byte H_Addr;    ///< Старший байт
                byte L_Addr;    ///< Младший байт
            };
        };
    }CMD; ///< Объект структуры команды

    /**
     * @brief data union - структура данных 4 байта
     */
    union data{
        int I;      ///< Либо целые
        float R;    ///< Либо вещественные
        struct {
            byte b1;    ///< Первый байт
            byte b2;    ///< Второй байт
            byte b3;    ///< Третий байт
            byte b4;    ///< Четвёртый байт
        };
    }DATA; ///< Объект структуры данных

    ///PSW (Cостояние процессора)
    struct bits
    {
        address IP; ///< Instruction Pointer
        bit SF:1;   ///< Sign flag результат положительный - 1
        bit ZF:1;   ///< Zero flag Резульат равен нулю - 1
        bit OF:1;   ///< Overflow flag переполнение
        bit :13;    ///< не используется
    }PSW; ///< Объект структуры состояния процессора

#pragma pack(pop)

    Command *pCMD[128] = {nullptr}; ///< набор команд процессора, инициализируется в конструкторе

    data        RS;     ///< Сумматор 4 байта
    address     RA;     ///< Адресный регистр 2 байта
    data        R1;     ///< Внутренний регистр

    /**
     * @brief MEM - Оперативная память
     *
     * Адресное пространство 16 бит. Байтовая.
     */
    byte *MEM = new byte[0xffff];
};

#endif // COMPUTER_H
