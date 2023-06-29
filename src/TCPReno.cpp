#include "TCPReno.hpp"




TCPConnection::TCPConnection(int &_cwnd, int &_ssthresh, int &_rtt, const string &_congestion_control_method){
    cwnd = _cwnd;                   // Initital congestion window size
    ssthresh = _ssthresh;           // Initial slow start threshold
    rtt = _rtt;
    congestion_control_method = _congestion_control_method;
    reno_state = "slow_start";
    // new_reno_state = ? 
    // bbr_state = ?
}

int TCPConnection::getCwnd(){
    return cwnd;
}

int TCPConnection::getSsthresh(){
    return ssthresh;
}

int TCPConnection::getRTT(){
    return rtt;
}

string TCPConnection::getCongestionControlMethod(){
    return congestion_control_method;
}

void TCPConnection::setCwnd(int _cwnd){
    cwnd = _cwnd;
}

void TCPConnection::setSsthresh(int _ssthresh){
    ssthresh = _ssthresh;
}

void TCPConnection::setRTT(int _rtt){
    rtt = _rtt;
}

void TCPConnection::setCongestionControlMethod(string _congestion_control_method){
    congestion_control_method = _congestion_control_method;
}

void TCPConnection::sendData(){
    if (congestion_control_method == "reno") {
        renoSendData();
    } else if (congestion_control_method == "new_reno") {
        newRenoSendData();
    } else if (congestion_control_method == "bbr") {
        bbrSendData();
    } else {
        cout << "Invalid congestion control method" << endl;
    }
}

void TCPConnection::renoSendData(){
    if (reno_state == "slow_start") {
        cwnd = cwnd * 2;
        if (cwnd >= ssthresh) {
            reno_state = "congestion_avoidance";
        }
    } else if (reno_state == "congestion_avoidance") {
        cwnd = cwnd + 1;
    } else if (reno_state == "fast_recovery") {
        cwnd = ssthresh;
        reno_state = "congestion_avoidance";
    } else {
        cout << "Invalid reno state" << endl;
    }
}

void TCPConnection::newRenoSendData(){
    // TODO
}

void TCPConnection::bbrSendData(){
    // TODO
}

void TCPConnection::onPacketLoss(){
    // TODO
}

void TCPConnection::onRTTUpdate(){
    // TODO
}




