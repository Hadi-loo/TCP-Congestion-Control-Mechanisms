# CN_CHomeworks4

This Repo contains a simulation of 3 famous TCP protocols, "TCP Reno", "TCP New Reno", and "TCP BBR" coded with C++.

## How to run
run the following commands in terminal:
```
make
./main.out
```

## Questions
#### 1. Difference of Congestion control and Flow control:
Flow control is a method used to regulate and manage the flow of data between nodes in a computer network.
By controlling the incoming flows from the senders, 
we can prevent buffer overflowing and make the network more efficient.      
In other hand, Congestion control is a method to prevent congestion in a network.
Congestion occurs when more than controlable data is being sent over a network,
and the network becomes overloaded. The main goal of this method is to prevent network
from being congested and make more efficient usage of the network resources.
Flow control is typically used in data link layer, but conestion control is applied in network and transport layer.

#### 2. Definition of TCP New Reno algorithm:
TCP New Reno is a congestion control algorithm used in computer networks, particularly in the
Transmission Control Protocol (TCP). It is an enhanced version of the original TCP Reno
algorithm and aims to improve network performance and fairness.    
The main enhancement in TCP New Reno compared to TCP Reno, is that the TCP New Reno works more
wisely in the fast recovery mechanism. In TCP Reno, when multiple a sender receives multiple
duplicate ACKs for several sent packets, it divides the congestion window size several times,
but in TCP New Reno, the algorithm only divides the congestino window size once, thus it is
works more effiecient than the normal TCP Reno algorithm.

#### 3. Definition of TCP New Reno algorithm:
TCP BBR, also known as Bottleneck Bandwidth and Round-trip propagation time, is an congestion control algorithm created by Google. Its primary goal is to maximize network utilization and minimize latency by dynamically estimating the available bandwidth and network latency. BBR adopts a model-based approach to determine the ideal sending rate for TCP flows, considering both the bottleneck bandwidth and the round-trip time of the network. By accurately measuring these parameters, BBR optimizes the transmission rate, reducing queuing delay, and enhancing overall network performance. It is particularly effective in high-speed and long-distance networks, delivering faster and more efficient data transfer compared to traditional TCP congestion control algorithms.

#### 4. Difference of TCP Reno, TCP New Reno, and TCP BBR:   
TCP Reno is the original and most widely used congestion control algorithm. It works with slow start, AIMD, fast recovery, and fast retransmit protocols.   
TCP New Reno is alomost like TCP Reno, but it works more wisely than TCP Reno in terms of fast recover, as described in part 3.     
TCP BBR, on the other hand, is a modern congestion control algorithm developed by google in 2016. in BBR, the main focues is on estimating the available bandwidth and network latency (round-trip-time), in order to find the bandwidth-latency product and calculating the most efficient congestion window size of the network. BBR dynamically adjusts its congestion window based on the measured network conditions, aiming to maximize both network utilization and minimize latency. It is particularly effective in high-speed and long-distance networks, providing faster and more efficient data transfer compared to traditional TCP congestion control algorithms.    






