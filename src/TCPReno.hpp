#ifndef __TCPRENO__
#define __TCPRENO__

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include <ctime>
#include "defs.hpp"

using namespace std;


class TCPConnection{
private:
    int cwnd;                       // Congestion window
    int ssthresh;                   // Slow start Threshold
    int rtt;                        // Round-trip time
    int bandwidth;                  // network bandwidth
    int last_ack;
    int acks_after_loss;
    int lost_count;
    int connection_mode;
    int reno_state;
    int bbr_state;
    int timeout;
    int in_flight_treshold;


public:
    TCPConnection(int _cwnd, int _ssthresh, int _rtt, int _connection_mode);
    bool sendData();
    void sendDataBBr();
    bool onPacketLoss(int connection_mode , int lost_packets_count);
    void onRTTUpdate(int _rtt);
    void onRTTUpdateBBR(int _rtt);
    void incRTT(int amount);
};


#endif