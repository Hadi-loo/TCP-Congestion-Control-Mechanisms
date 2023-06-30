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
    cwnd = _cwnd;                    // Initital congestion window size
    ssthresh = _ssthresh;            // Initial slow start threshold
    rtt = _rtt;                      // Initial round-trip time
    bandwidth = 512;                 // network bandwidth
    last_ack = 0;
    acks_after_loss = 0;
    lost_count = 0;
    connection_mode = _connection_mode;
    reno_state = SLOW_START;
    bbr_state = START_UP;
    timeout = 0;
    in_flight_treshold = IN_FLIGHT_THRESHOLD;
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

    else if (connection_mode == TCP_BBR) {
        cout << "RTT:  " << rtt << ",\t\tcwnd: " << cwnd << ",\t\tstate:" << bbr_state << endl;
        // cout << cwnd << endl;    // This is for plotting
        
        if (last_ack >= MAX_PACKETS) {
            cout << RED << "Max packets reached" << RESET << endl;
            return true;
        }

        int first = last_ack + acks_after_loss;  
        int last = first + cwnd - 1;
        lost_count = 0;
        acks_after_loss = 0;
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
            }
        }

        if (bbr_state == STEADY && rtt % 10 == 0) {
            cwnd *= PROB_WB_ASCENT_RATE;
            bbr_state = PROBE_BW;
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

    else if (connection_mode == TCP_BBR) {
        return false;
    }

    return false;
}

void TCPConnection::onRTTUpdate(int _rtt) {
    
    if (connection_mode == TCP_RENO || connection_mode == TCP_NEW_RENO) {
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

    else if (connection_mode == TCP_BBR) {
        switch (bbr_state) {
            case START_UP:
                cwnd += cwnd;
                if (cwnd >= in_flight_treshold) {
                    cwnd = in_flight_treshold;
                    bbr_state = DRAIN;
                }
                break;
            case DRAIN:
                cwnd *= DRAIN_RATIO;
                if (cwnd < bandwidth) {
                    cwnd *= PROB_WB_ASCENT_RATE;
                    bbr_state = PROBE_BW;
                }
                break;
            case PROBE_BW:
                cwnd *= PROB_WB_DESCENT_RATE;
                if (cwnd < bandwidth) {
                    bbr_state = STEADY;
                }
                break;
            case STEADY:
                cwnd = bandwidth;
                break;
            default:
                break;
        }
    }
}
