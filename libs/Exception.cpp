/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#include <cstdarg>
#include <sstream>
#include <string>

#include "Exception.h"
/**
 * Se adapto la clase OSError, usando funciones estandar de C++11, para hacer
 * una clase genérica Exception
 * @param fmt = Formato al cual completar
 * @param ... = argumentos para completar fmt
 */
Exception::Exception(const char *fmt, ...) noexcept {
    std::istringstream iss(fmt);
    std::ostringstream oss;
    std::string stringFragment;

    va_list args;
    va_start(args, fmt);
    while (std::getline(iss, stringFragment, '%')) {
        oss << stringFragment;
        char type(0);
        iss >> type;
        switch (type) {
            case 's':
                oss << va_arg(args, const char *);
                break;
            case 'S':
                break;
            case 'i':
                oss << va_arg(args, int);
                break;
            case 'f':
                oss << va_arg(args, float);
                break;
            default:
                break;
        }
    }
    oss << '\0';
    va_end(args);
    this->msg_error = oss.str();
}

const char *Exception::what() const noexcept {
    return this->msg_error.data();
}
