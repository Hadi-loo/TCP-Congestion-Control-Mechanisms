#include "TCPReno.hpp"



int main(){
    TCPConnection connection1(1, 65535, 0);
    
    // connection1.sendData();
    // connection1.onRTTUpdate(2);

    connection1.sendDataBBr();
    







}