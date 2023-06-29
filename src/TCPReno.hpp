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
    void sendData();
    void onPacketLoss();
    void onRTTUpdate(int _rtt);
    
};


#endif