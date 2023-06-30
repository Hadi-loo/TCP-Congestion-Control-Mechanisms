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

#### 3. Definition of TCP BBR algorithm:
TCP BBR, also known as Bottleneck Bandwidth and Round-trip propagation time, is an congestion control algorithm created by Google. Its primary goal is to maximize network utilization and minimize latency by dynamically estimating the available bandwidth and network latency. BBR adopts a model-based approach to determine the ideal sending rate for TCP flows, considering both the bottleneck bandwidth and the round-trip time of the network. By accurately measuring these parameters, BBR optimizes the transmission rate, reducing queuing delay, and enhancing overall network performance. It is particularly effective in high-speed and long-distance networks, delivering faster and more efficient data transfer compared to traditional TCP congestion control algorithms.

#### 4. Difference of TCP Reno, TCP New Reno, and TCP BBR:   
TCP Reno is the original and most widely used congestion control algorithm. It works with slow start, AIMD, fast recovery, and fast retransmit protocols.   
TCP New Reno is alomost like TCP Reno, but it works more wisely than TCP Reno in terms of fast recover, as described in part 3.     
TCP BBR, on the other hand, is a modern congestion control algorithm developed by google in 2016. in BBR, the main focues is on estimating the available bandwidth and network latency (round-trip-time), in order to find the bandwidth-latency product and calculating the most efficient congestion window size of the network. BBR dynamically adjusts its congestion window based on the measured network conditions, aiming to maximize both network utilization and minimize latency. It is particularly effective in high-speed and long-distance networks, providing faster and more efficient data transfer compared to traditional TCP congestion control algorithms.    


#### 5. Evaluating the simluation of TCP Reno, TCP New Reno, and TCP BBR:    


#### 6. Describing other congestion avoidance protocols and comparing them with algorithms that provided in this project:
- **Compound TCP**: Compound TCP (CTCP) is a congestion control algorithm developed by Microsoft for use in Windows operating systems. It is designed to optimize TCP performance in high-speed and high-delay networks. CTCP combines two congestion control algorithms: the traditional TCP Reno and the TCP Vegas.
- **TCP Hybla**: TCP Hybla is a congestion control algorithm developed by the Politecnico di Torino in Italy. It is designed to improve the performance of TCP in networks with high bandwidth and long round-trip times (RTTs). TCP Hybla aims to address the inherent limitations of traditional TCP Reno, which may experience poor throughput and excessive delay in such network conditions.
- **TCP Cubic**: CUBIC (Cubic Congestion Control) is a TCP congestion control algorithm designed to provide efficient and fair bandwidth utilization in modern networks. CUBIC aims to address the limitations of traditional TCP Reno congestion control, which can lead to suboptimal performance in high-speed, long-distance networks. CUBIC uses a different approach to determine the appropriate sending rate and congestion window size.Unlike Reno, which uses a linear growth pattern, CUBIC employs a cubic growth pattern for the congestion window. It allows for a more aggressive increase in the sending rate during the congestion avoidance phase, maximizing throughput and reducing latency.


TCP Cubic is works better than TCP Reno, New Reno, and BBR in terms of the needed convergence time to the maximum possible CWND size in the network. Contrary to other protocols, it uses a cubic function to calculate the size of the congestion window, which results in a more aggressive slope of raising the window size at low congestion times and a less aggressive slope at high congestion times.  







