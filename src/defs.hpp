#ifndef __defs__
#define __defs__


#define SEND_DATA_CYCLES 20
#define AIMD_INCREASE_RATE 1
#define MAX_PACKETS 250000
#define RETRANSMIT_TRIGGER 3
#define TIMEOUT 5
#define DRAIN_RATIO 0.9
#define PROB_WB_ASCENT_RATE 1.25
#define PROB_WB_DESCENT_RATE 0.95
#define IN_FLIGHT_THRESHOLD 1024

// TCP RENO MODES
#define SLOW_START 0
#define CONGESTION_AVOIDANCE 1
#define FAST_RECOVERY 2
#define FAST_RETANSMIT 3

// TCP BBR MODES
#define START_UP 0
#define DRAIN 1
#define PROBE_BW 2
#define PROBE_RTT 3
#define STEADY 4

// connection modes
#define TCP_RENO 0
#define TCP_NEW_RENO 1
#define TCP_BBR 2

// colors
#define BLACK                               "\033[0;30m"
#define RED                                 "\033[0;31m"
#define GREEN                               "\033[0;32m"
#define YELLOW                              "\033[0;33m"
#define BLUE                                "\033[0;34m"
#define MAGENTA                             "\033[0;35m"
#define CYAN                                "\033[0;36m"
#define WHITE                               "\033[0;37m"
#define RESET                               "\033[0m"

#endif