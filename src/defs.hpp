#ifndef __defs__
#define __defs__


#define SEND_DATA_CYCLES 20
#define AIMD_INCREASE_RATE 3

// TCP RENO MODES
#define SLOW_START 0
#define CONGESTION_AVOIDANCE 1
#define FAST_RECOVERY 2

// TCP BBR MODES
#define START_UP 0
#define DRAIN 1
#define PROBE_BW 2
#define PROBE_RTT 3


// connection modes
#define TCP_RENO 0
#define TCP_NEW_RENO 1
#define TCP_BBR 2



#endif