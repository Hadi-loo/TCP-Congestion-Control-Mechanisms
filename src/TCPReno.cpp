#include "TCPReno.hpp"


void pretty_timer(int &rtt){
    for (int i = 0 ; i < 5; i++){
        cout << " . ";
        sleep(rtt/5);
    }
}

TCPConnection::TCPConnection(int _cwnd, int _ssthresh, int _rtt){
    cwnd = _cwnd;                   // Initital congestion window size
    ssthresh = _ssthresh;           // Initial slow start threshold
    rtt = _rtt;                     // Initial round-trip time
}

void TCPConnection::sendData(bool newReno = false, int lost_packets_count = 1){
    // Slow start
    int mode = SLOW_START;
    for (int i = 0; i < SEND_DATA_CYCLES; i++){
        sleep(1);
        switch (mode)
        {
        case SLOW_START:
            for(cwnd; cwnd < ssthresh; cwnd += cwnd){
                // cout << "--------------------------------------" << endl;
                // cout << "Current congestion window size is: " << cwnd;
                // cout << "Sending data";
                // pretty_timer(this->rtt);
                // cout << endl << "--------------------------------------" << endl;
            }
            cout << "--------------------------------------" << endl;
            cout << "Mode: Slow Start" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            mode = FAST_RECOVERY;
            break;

        case CONGESTION_AVOIDANCE:
            for(cwnd; cwnd < ssthresh; cwnd += AIMD_INCREASE_RATE){
                // cout << "--------------------------------------" << endl;
                // cout << "Current congestion window size is: " << cwnd;
                // cout << "Sending data";
                // pretty_timer(this->rtt);
                // cout << endl << "--------------------------------------" << endl;
            }
            cout << "--------------------------------------" << endl;
            cout << "Mode: Congestion Avoidance" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            mode = FAST_RECOVERY;
            break;

        case FAST_RECOVERY:
            if(newReno == true)
                cwnd /= 2;
            else
                cwnd /= lost_packets_count;

            mode = CONGESTION_AVOIDANCE;
            cout << "--------------------------------------" << endl;
            cout << "Fast Recovery Activated" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            break;

        default:
            break;
        }
    }
    return;
}

void TCPConnection::onPacketLoss(int connection_mode , int lost_packets_count){
    cout << "--------------------------------------" << endl;
    cout << "Duplicate ACKs received" << endl;
    cout << "--------------------------------------" << endl;
    if(connection_mode == TCP_RENO)
        this->sendData();
    else if(connection_mode == TCP_NEW_RENO)
        this->sendData(true, lost_packets_count);
    else if(connection_mode == TCP_BBR)
        this->sendDataBBr();
    return;
}

void TCPConnection::onRTTUpdate(int _rtt){
    this->rtt = _rtt;
    cout << "--------------------------------------" << endl;
    cout << "RTT time updated to: " << this->rtt << endl;
    cout << "--------------------------------------" << endl;
    return;
}

void TCPConnection::sendDataBBr(){
    int mode = START_UP;


    for (int i = 0; i < SEND_DATA_CYCLES; i++){
        sleep(1);
        switch (mode)
        {
        case START_UP:
            for(cwnd; cwnd < ssthresh; cwnd *= cwnd){}
            cout << "--------------------------------------" << endl;
            cout << "Mode: Start Up" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            mode = DRAIN;
            break;

        case DRAIN:
            
            break;

        case PROBE_BW:

            break;

        case PROBE_RTT:

            break;


        default:
            break;
        }
    }
}
