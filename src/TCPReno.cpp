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

void TCPConnection::sendData(){
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
            cwnd /= 2;
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
}

void TCPConnection::onPacketLoss(){
    cout << "--------------------------------------" << endl;
    cout << "3 duplicate ACK received" << endl;
    cout << "--------------------------------------" << endl;
    this->sendData();
}

void TCPConnection::onRTTUpdate(int _rtt){
    this->rtt = _rtt;
    cout << "--------------------------------------" << endl;
    cout << "RTT time updated to: " << this->rtt << endl;
    cout << "--------------------------------------" << endl;
}

