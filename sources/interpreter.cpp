#include "interpreter.h"

interpreter::~interpreter()
{
    delete VM;
}

/**
 * @brief interpreter::startVM - Запуск интерпретатора
 *
 * Отправка отладочных ссобщений. Инициализация и запуск вртуальной машины.
 */
void interpreter::startVM()
{
     VM = new Computer(ProgramPath,this);
     emit debugMSG("Запуск программы " + ProgramPath);
     int result = VM->execute();

     emit debugMSG("Программа завершилась с кодом " +
                   QString::number(result) + "\n\n");
     delete this;
}

/**
 * @brief interpreter::inputDialog - запрос на вывод диалогового окна для ввода значения
 * @param text - Текст сообшения для пользователя
 * @return Возвращает введённую пользователем строку
 *
 * Запрос на вывод диалогового окна для ввода у GUI.
 */
QString interpreter::inputDialog(QString text)
{
    bool bOk;
    QString str = QInputDialog::getText( 0, text, "Значение",
                                         QLineEdit::Normal,
                                         "", &bOk );
    if (bOk) {
        return str;
    }else return inputDialog(text);
}

/**
 * @brief interpreter::outputDialog - запрос на вывод диалогового окна для вывода сообщения
 * @param str - текст сообщения
 *
 * Запрос на вывод диалогового окна с сообщением для пользователя из GUI
 */
void interpreter::outputDialog(QString str)
{
    QMessageBox message;
    message.setWindowTitle("Сообщение");
    message.setText(str);
    message.exec();
}

/**
 * @brief interpreter::debug - Запрос на вывод сообщения от программы у GUI
 * @param msg - сообщение
 */
void interpreter::debug(QString  msg)
{
    emit debugMSG("Программа#: " + msg);
}

