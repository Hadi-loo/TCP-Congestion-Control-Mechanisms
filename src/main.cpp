#include "TCPReno.hpp"
#include <iostream>

int main() {
    int cwnd = 1;
    int ssthresh = 65535;
    int rtt = 0;
    TCPConnection tcp(cwnd, ssthresh, rtt, "reno");

    
}