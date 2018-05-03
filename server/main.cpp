/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#include <iostream>
#include <vector>
#include <string>

#include "../common/CommunicationSocket.h"
#include "ServerSocket.h"

int main(){
    std::string port("1051");
    ServerSocket s(port.data());
    std::cout << "Se bindeo" << std::endl;
    CommunicationSocket c = s.accept();
    std::cout << "hubo conexión" << std::endl;
    std::string bye = "chau";
    std::vector<char> buffer(5, 0);
    c.receive(buffer.data(), 4);

    std::cout << buffer.data() << std::endl;
    c.send(bye.data(), 4);
    return 0;
}
