/*
 * Federico Manuel Gomez Peter 
 * Date: 17/05/18.
 */
#include <exception>
#include <iostream>

#include "GameStateMsg.h"
#include "Stream.h"

int main(int argc, const char *argv[]){
    try {
        IO::Stream<IO::GameStateMsg> server_stream;
        IO::Stream<IO::PlayerInput> player_stream;
    } catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(...){
        std::cerr << "Unkown error in main thread" << std::endl;
        return 1;
    }
    return 0;
}