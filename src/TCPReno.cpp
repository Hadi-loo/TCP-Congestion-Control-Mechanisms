#include "TCPReno.hpp"




TCPConnection::TCPConnection(int &_cwnd, int &_ssthresh, int &_rtt){
    cwnd = _cwnd;                   // Initital congestion window size
    ssthresh = _ssthresh;           // Initial slow start threshold
    rtt = _rtt;
}

void TCPConnection::sendData(){
    // TODO
}

void TCPConnection::onPacketLoss(){
    // TODO
}

void TCPConnection::onRTTUpdate(){
    // TODO
}




