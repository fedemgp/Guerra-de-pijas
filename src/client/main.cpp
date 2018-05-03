/*
 * Created by Federico Manuel Gomez Peter 
 * Date: 02/05/2018.
 */
#include <iostream>
#include <string>
#include <vector>

#include "ClientSocket.h"

int main(){
    std::string host = "localhost";
    std::string port = "1051";
    ClientSocket c(host.data(), port.data());
    std::cout << "Se conecto al servidor" << std::endl;
    std::string hello = "hola";
    std::vector<char> buffer(5,'\0');
    c.send(hello.data(), 4);
    c.receive(buffer.data(), 4);

    std::cout << buffer.data() << std::endl;
    return 0;
}
