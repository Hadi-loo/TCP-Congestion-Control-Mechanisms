#ifndef __TCPRENO__
#define __TCPRENO__

#include <iostream>
// #include <cstdlib>
#include <unistd.h>
#include "defs.hpp"

using namespace std;


class TCPConnection{
private:
    int cwnd;                       // Congestion window
    int ssthresh;                   // Slow start Threshold
    int rtt;                        // Round-trip time


public:
    TCPConnection(int _cwnd, int _ssthresh, int _rtt);
    void sendData(bool newReno = false, int lost_packets_count = 1);
    void sendDataBBr();
    void onPacketLoss(int connection_mode , int lost_packets_count);
    void onRTTUpdate(int _rtt);
    
};


#endif