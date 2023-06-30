#include "TCPReno.hpp"



int main(){
    TCPConnection connection1(1, 65535, 0, TCP_NEW_RENO);
    
    while (!connection1.sendData()) {
        if (!connection1.onPacketLoss(TCP_NEW_RENO, 1)) {
            connection1.onRTTUpdate(1);
        }
        connection1.incRTT(1);
    }

    // TCP Reno with 1 packet loss
    // connection1.sendData();
    // connection1.onPacketLoss(TCP_RENO, 1);

    // Updating RTT
    // connection1.onRTTUpdate(2);

    // TCP Reno with 3 packet loss
    // connection1.sendData(false, 3);
    // connection1.onPacketLoss(TCP_RENO, 3);

    // Updating RTT
    // connection1.onRTTUpdate(3);

    // TCP New Reno with 3 packet loss
    // connection1.sendData(true, 3);
    // connection1.onPacketLoss(TCP_NEW_RENO, 3);

    // Updating RTT
    // connection1.onRTTUpdate(1);

    // TCP BBR
    // connection1.sendDataBBr();
    // connection1.onPacketLoss(TCP_BBR, 3);
    


}