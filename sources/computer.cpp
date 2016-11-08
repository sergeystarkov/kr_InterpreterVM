#include "computer.h"
#include "interpreter.h"


/**
 * @brief Computer::Computer - конструктор
 * @param PATH - путь до файла программы
 * @param INTER - указатель на объект родитель
 *
 * Инициализирует массив команд процессора, и переменные.
 */
Computer::Computer(QString PATH,interpreter *INTER)
{
    programPath = PATH;     //Путь до программы
    Interpreter = INTER;    //Указатель на родителя

    pCMD[STOP]  =   new cSTOP();    //Остановка

    //Целая арифметика
    pCMD[Iadd]  =   new cIadd();    //Целочисленное сложение
    pCMD[Isub]  =   new cIsub();    //Целочисленное вычитание
    pCMD[Imul]  =   new cImul();    //Целочисленное умножение
    pCMD[Idiv]  =   new cIdiv();    //Целочисленное деление
    pCMD[Imod]  =   new cImod();    //Целочисл. остаток от деления
    pCMD[Iin]   =   new cIin();     //Ввод целого числа
    pCMD[Iout]  =   new cIout();    //Вывод целого числа

    //Дробная арифметика
    pCMD[Radd]  =   new cRadd();    //Вещественное сложение
    pCMD[Rsub]  =   new cRsub();    //Вещественное вычитание
    pCMD[Rmul]  =   new cRmul();    //Вещественное умножение
    pCMD[Rdiv]  =   new cRdiv();    //Вещественное деление
    pCMD[Rin]   =   new cRin();     //Ввод вещественного числа
    pCMD[Rout]  =   new cRout();    //Вывод вещественного числа

    //Операции с сумматором
    pCMD[Load]  =   new cLoad();    //Загрузка сумматора
    pCMD[Store] =   new cStore();   //Сохранение сумматора

    pCMD[Radr]  =   new cRadr();    //Загрузка адресного регистра константой

    //прыжки
    pCMD[Jmp]   =   new cJmp();     //Безусловный переход
    pCMD[JZ]    =   new cJZ();      // ==
    pCMD[JG]    =   new cJG();      // >
    pCMD[JL]    =   new cJL();      // <

    //сравнение cIcmp
    pCMD[Icmp]  =   new cIcmp();    //Целочисленное сравнение
    pCMD[Rcmp]  =   new cRcmp();    //Вещественное сравнение
}

//Деструктор
Computer::~Computer()
{
    for( int i = 0 ; i < 128 ; i++ ) {
        delete pCMD[i];
    }
    delete[] MEM;
}

/**
 * @brief Computer::load
 * @return true в случае успешной загрузки
 *
 * Загружает файл программы в оперативную память.
 * Производит простой синтаксический анализ.
 * В случае синтаксической ошибки возвращает false
 */
bool Computer::load()
{
    QFile file(programPath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        int curByte = 0;
        while(!file.atEnd()){
            if(curByte >= 0xfffd) return false; //Защита от переполнения ОЗУ
            QStringList strline = QString(file.readLine()).simplified().split(' ');
            if(strline.count() <= 0) break;

            CMD.Cmd = (byte)strline[0].toUInt();

            if(strline.count() >= 2)
                CMD.Addr = (address)strline[1].toUInt();
            else CMD.Addr = 0;

            //Загрузка программы в ОЗУ
            MEM[curByte++] = CMD.Cmd;
            MEM[curByte++] = CMD.H_Addr;
            MEM[curByte++] = CMD.L_Addr;

        }
        RA += curByte; //Адресный регистр для данных после программы
    }else {
        return false;
    }
    if(file.isOpen()) file.close();
    return true;
}

/**
 * @brief Computer::reset Сброс регистров
 *
 * Инициализация и сброс регистров компьютера до исходных значений.
 */
void Computer::reset()
{
    PSW.IP = 0x0000;
    PSW.OF = 0;
    PSW.SF = 0;
    PSW.ZF = 0;
    RA = 0x0000;
    RS.I = 0;
    R1.I = 0;
}

/**
 * @brief Computer::run - цикл процессора
 * @return Код завершения выполнения программы
 *
 * Поочерёдно выполняет машинные инструкции из ОЗУ.
 */
int Computer::run()
{
    while(true)
    {
        if(PSW.IP >= 0xFFFC) return 4;
        //Загрузка команды в структуру
        CMD.Cmd     =   MEM[ PSW.IP++ ];   //Формируем структуру 3 байта из памяти
        CMD.H_Addr  =   MEM[ PSW.IP++ ];
        CMD.L_Addr  =   MEM[ PSW.IP++ ];
        //*************************************
        if(CMD.OP > 256) continue;  //Защита от некорректной команды
        if(pCMD[CMD.OP] == NULL) return 3;  //Защита от неизвестной команды
        int execResult = pCMD[ CMD.OP ]->operator ()(this);     //Выполнение
        if( execResult != 1) return execResult;                 //Результат выполнения
    }
    return 0;
}

/**
 * @brief Computer::flagI - Установка флага для целых чисел
 *
 * Устанавливает флаги для целочисленного сумматора
 */
void Computer::flagI()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.I == 0) PSW.ZF = 1;
    else if(RS.I > 0) PSW.SF = 1;
}

/**
 * @brief Computer::flagR - Установка флага для вещественных чисел
 *
 * Устанавливает флаги для вещественного сумматора
 */
void Computer::flagR()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.R == 0) PSW.ZF = 1;
    else if(RS.R > 0) PSW.SF = 1;
}

/**
 * @brief Computer::execute - алгоритм запуска программы
 * @return Код завершения выполнения программы
 *
 * Сбрасывает регистры.
 * Загружает программу в память.
 * Запускает прцессор.
 */
int Computer::execute()
{
    this->reset();
    if(!this->load())
    {
        return 2;
    }
    return this->run();
}

//Обработчик прерываний
/**
 * @brief Computer::interrupt - Обработчик прерываний
 * @param interruptCode
 *
 * Обрабатывает 4 прерывания - ввод/вывод целого/вещественного числа
 */
void Computer::interrupt(int interruptCode)
{
    switch (interruptCode){
    case hIin: {//Ввод целого значения сумматора
        DATA.I = Interpreter->inputDialog("Введите целое число").toInt();
        break;
    }
    case hRin: {//Ввод вещественного значения сумматора
        DATA.R = Interpreter->inputDialog("Введите вещественное число").toFloat();
        break;
    }
    case hIout:{//Вывод целого значения сумматора на экран
        QString str = QString::number(RS.I);
        Interpreter->outputDialog(str);
        break;
    }
    case hRout: {//Вывод вещественного значения сумматора на экран
        QString str = QString::number(RS.R,'f',2);
        Interpreter->outputDialog(str);
        break;
    }
    }
}

/**
 * @brief Computer::debug - Отладочное сообщение
 * @param msg - Текст сообщения
 *
 * Отправляет текст отладочного сообщения интерпретатору
 */
void Computer::debug(QString msg)
{
    Interpreter->debug(msg);
}
