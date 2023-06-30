#include "TCPReno.hpp"


void pretty_timer(int &rtt){
    for (int i = 0 ; i < 5; i++){
        cout << " . ";
        sleep(rtt/5);
    }
    cout << endl;
}

bool packetLost(int cwnd) {
    // srand(static_cast<unsigned>(time(nullptr)));
    int random = rand() % 500000;
    if (cwnd > 1024 && random < 100)
        return true;
    else if (cwnd > 512 && random < 50)
        return true;
    else if (cwnd > 256 && random < 10)
        return true;
    else if (cwnd > 128 && random < 5)
        return true;
    else if (cwnd > 64 && random < 2)
        return true;
    else if (cwnd > 16 && random < 1)
        return true;
    else
        return false;
}

TCPConnection::TCPConnection(int _cwnd, int _ssthresh, int _rtt, int _connection_mode){
    cwnd = _cwnd;                   // Initital congestion window size
    ssthresh = _ssthresh;           // Initial slow start threshold
    rtt = _rtt;                     // Initial round-trip time
    bandwidth = 1000;               // network bandwidth
    last_ack = 0;
    acks_after_loss = 0;
    lost_count = 0;
    connection_mode = _connection_mode;
    reno_state = SLOW_START;
    timeout = 0;
}

void TCPConnection::incRTT(int amount) {
    rtt += amount;
}

bool TCPConnection::sendData(){
    
    if (connection_mode == TCP_RENO || connection_mode == TCP_NEW_RENO) {
        cout << "RTT:  " << rtt << ",\t\tcwnd: " << cwnd << ",\t\tssthresh:" << ssthresh << endl;
        // cout << cwnd << endl;    // This is for plotting
        
        if (timeout != 0) {
            return false;
        }
        if (last_ack >= MAX_PACKETS) {
            cout << RED << "Max packets reached" << RESET << endl;
            return true;
        }

        int first = (connection_mode == TCP_RENO) ? last_ack : last_ack + acks_after_loss;  // first unacked packet
        int last = first + cwnd - 1;    
        lost_count = 0;
        acks_after_loss = 0;
        int temp_last_ack = last_ack;
        for (int i = first; i < last; i++) {
            if (packetLost(cwnd)) {
                // cout << "cwnd: " << cwnd << ",\t\tssthresh:" << ssthresh << endl;        // just to see loss points
                cout << RED << "Packet " << i << " lost" << RESET << endl; 
                lost_count++;
            }
            else if (lost_count == 0) {
                last_ack++;
            }
            else {
                acks_after_loss++;
                if (acks_after_loss == RETRANSMIT_TRIGGER) {
                    return false;
                }
            }
        }
    }
    return false;
}

bool TCPConnection::onPacketLoss(int connection_mode , int lost_packets_count){
    
    if (connection_mode == TCP_RENO || connection_mode == TCP_NEW_RENO) {
        if (timeout != 0) {
            timeout--;
            return true;
        }
        else if (acks_after_loss >= RETRANSMIT_TRIGGER) {
            reno_state = FAST_RETANSMIT;
            if (connection_mode == TCP_NEW_RENO) {
                ssthresh = cwnd / 2;
            } else if (connection_mode == TCP_RENO) {
                ssthresh = cwnd / pow(2, lost_count);
            }
            cwnd = ssthresh;
            return true;
        }
        else if (lost_count != 0) {
            timeout = TIMEOUT;
            reno_state = SLOW_START;
            if (connection_mode == TCP_NEW_RENO) {
                ssthresh = cwnd / 2;
            } else if (connection_mode == TCP_RENO) {
                ssthresh = cwnd / pow(2, lost_count);
            }
            cwnd = 1;
            return true;
        }
        return false;
    }
    return false;
}

void TCPConnection::onRTTUpdate(int _rtt) {
    switch (reno_state) {
        case FAST_RETANSMIT:
            reno_state = CONGESTION_AVOIDANCE;
        case CONGESTION_AVOIDANCE:
            cwnd += AIMD_INCREASE_RATE;
            break;
        case SLOW_START:
            cwnd += cwnd;
            if (cwnd >= ssthresh) {
                cwnd = ssthresh;
                reno_state = CONGESTION_AVOIDANCE;
            }
            break;
        default:
            break;
    }
}

void TCPConnection::onRTTUpdateBBR(int _rtt){
    this->rtt = _rtt;
    cout << "--------------------------------------" << endl;
    cout << "New RTT captured time: " << this->rtt << endl;
    cout << "--------------------------------------" << endl;
    return;
}

void TCPConnection::sendDataBBr(){
    int mode = START_UP;
    int bandwidth = 1000;
    int drain_rate = 25;
    int rtt_increase_rate = 15;
    int rtt_decrease_rate = 20;
    int rtt_impact_rate = 3;
    int bandwidth_impact_rate = 3;

    for (int i = 0; i < SEND_DATA_CYCLES; i++){
        sleep(1);
        switch (mode)
        {
        case START_UP:
            /*
            Start to increase congestion window size like what we had in TCP RENO
            */
            
            for(cwnd; cwnd < ssthresh; cwnd += cwnd){}
            cout << "--------------------------------------" << endl;
            cout << "Mode: Start Up" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            mode = DRAIN;
            break;

        case DRAIN:
            /*
            Decrease the window size with the DRAIN_RATE parameter
            */
            for(cwnd; cwnd > ssthresh; cwnd -= drain_rate)
            cout << "--------------------------------------" << endl;
            cout << "Mode: DRAIN" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            mode = PROBE_BW;
            break;

        case PROBE_BW:
            /*
            Calculate the estimated bandwidth for current time
            */
            if(cwnd > ssthresh){
                cwnd -= bandwidth_impact_rate;
            }
            else if(cwnd < ssthresh){
                cwnd += bandwidth_impact_rate;
            }
            cout << "--------------------------------------" << endl;
            cout << "Mode: PROBE_BW" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            mode = PROBE_RTT;

            break;

        case PROBE_RTT:
            /*
            Calculate the estimated rtt for current time
            */
            if(cwnd > ssthresh){
                onRTTUpdateBBR(rtt_increase_rate);
                cwnd -= rtt_impact_rate;
            }
            else if(cwnd < ssthresh){
                onRTTUpdateBBR(rtt_decrease_rate);
                cwnd += rtt_impact_rate; 
            }
            cout << "--------------------------------------" << endl;
            cout << "Mode: PROBE_RTT" << endl;
            cout << "Last congestion window size is: " << cwnd;
            cout << endl << "--------------------------------------" << endl;
            mode = PROBE_BW;

            break;

        default:
            break;
        }
    }
}
