#ifndef __TCPRENO__
#define __TCPRENO__

#include <iostream>


using namespace std;


class TCPConnection{
private:
    int cwnd;                       // Congestion window
    int ssthresh;                   // Slow start Threshold
    int rtt;                        // Round-trip time
    string congestion_control_method;
    string reno_state;
    string new_reno_state;
    string bbr_state;


public:
    TCPConnection(int &_cwnd, int &_ssthresh, int &_rtt, const string &_congestion_control_method);
    
    int getCwnd();
    int getSsthresh();
    int getRTT();
    string getCongestionControlMethod();

    void setCwnd(int _cwnd);
    void setSsthresh(int _ssthresh);
    void setRTT(int _rtt);
    void setCongestionControlMethod(string _congestion_control_method);
    
    void sendData();
    void renoSendData();
    void newRenoSendData();
    void bbrSendData();
    void onPacketLoss();
    void onRTTUpdate();

    
};


#endif