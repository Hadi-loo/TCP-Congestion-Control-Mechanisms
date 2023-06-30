![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/4efaffe5-6044-427c-9229-6cba20e65a81)# CN_CHomeworks4

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

## TCP Reno

TCP Reno is a classic congestion control method that is widely used in TCP (Transmission Control Protocol) to manage and avoid network congestion. It is an enhancement to the original TCP Tahoe congestion control algorithm and is known for its efficiency and stability in handling congestion in the Internet.

TCP Reno operates based on the principle of "Additive Increase, Multiplicative Decrease" (AIMD), which means that it gradually increases the sending rate when the network is not congested and reduces it significantly when congestion is detected.

This method is implemented in TCP Reno through the following phases:

1. **Slow Start:**
   - When a TCP connection is established or re-established, it enters the slow-start phase.
   - In slow start, the sender starts by sending a small number of packets (usually one segment) and doubles the sending rate for each successful round-trip time (RTT) until it detects congestion or reaches the congestion window size (cwnd).

2. **Congestion Avoidance:**
   - Once the congestion window size (cwnd) exceeds a certain threshold (ssthresh), TCP Reno switches from slow start to congestion avoidance phase.
   - In the congestion avoidance phase, the sender increases the cwnd more conservatively by incrementing it by 1 segment per RTT, rather than doubling it as in slow start.
   - This gradual increase allows TCP to probe the network for available bandwidth without causing rapid congestion.

3. **Fast Recovery:**
   - When a packet loss is detected (e.g., due to a timeout or triple duplicate ACKs), TCP Reno enters the fast recovery phase.
   - In fast recovery, TCP reduces the congestion window size to half of the current cwnd (ssthresh is also adjusted to half of cwnd).
   - The sender then retransmits the lost packet(s) without going back to the slow-start phase.
   - TCP Reno also keeps track of the number of duplicate ACKs received during this phase.

4. **Fast Retransmit:**
   - If TCP Reno receives three duplicate ACKs (indicating a packet loss), it assumes that a segment has been lost from the current window and performs a fast retransmit.
   - Instead of waiting for a retransmission timeout (RTO), TCP Reno quickly retransmits the missing segment.

5. **AIMD After Fast Recovery:**
   - After the fast recovery phase, TCP Reno resumes congestion avoidance phase but with a slightly different approach compared to its original AIMD behavior.
   - Instead of starting with a congestion window of 1 segment, TCP Reno starts with the new value of cwnd after the fast recovery.
   - This modification helps maintain a higher sending rate after fast recovery and allows a quicker return to a stable state.

TCP Reno's AIMD behavior helps it find the optimal sending rate, maximizing throughput while efficiently responding to congestion signals. The gradual increase in cwnd during congestion avoidance and the aggressive reduction during fast recovery enable TCP Reno to handle congestion events effectively and avoid excessive queuing and packet loss. TCP Reno's approach has been instrumental in shaping the modern Internet, contributing to its stability and reliability in handling diverse network conditions.

Here is some of the results of the simulation of TCP Reno:

- RENO with low packet loss rate and sshtresh = 65535
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/50390931-9d74-46fe-9168-fc35e4bb30c8)

- RENO with low packet loss rate and sshtresh = 256
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/fad58f52-e585-407f-9bdf-2b64581b5a0d)

- RENO with high packet loss rate and sshtresh = 65535
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/b99e7734-38dc-4a6c-902c-3615b462e28c)

As we can see, when the packet loss rate is low, the congestion window size increases gradually and the throughput increases linearly. But when the packet loss rate is high, the congestion window size decreases rapidly and the throughput decreases linearly. So the overall performance of our connection gets worse by increasing the packet loss rate.

Also by decreasing ssthresh, we exit the slow start phase sooner and enter the congestion avoidance phase.

## TCP New Reno

TCP New Reno is an enhancement to the classic TCP Reno congestion control algorithm. It is designed to improve the performance and efficiency of TCP Reno, especially in scenarios with multiple packet losses within a single window of data. TCP New Reno addresses a limitation in TCP Reno's handling of multiple packet losses by allowing for a more precise recovery mechanism.

Here's how TCP New Reno works in full detail:

1. **Slow Start and Congestion Avoidance:**
   - TCP New Reno's slow start and congestion avoidance phases are the same as in TCP Reno. It starts by sending a small number of packets and doubles the congestion window size (cwnd) during slow start until it reaches the congestion window threshold (ssthresh). Then, it increases cwnd more conservatively in the congestion avoidance phase.

2. **Fast Recovery:**
   - When a packet loss is detected, TCP New Reno enters the fast recovery phase, just like TCP Reno.
   - During fast recovery, instead of reducing the congestion window size (cwnd) to half, like in TCP Reno, TCP New Reno reduces cwnd by the number of packets that have been acknowledged since entering the fast recovery state.
   - This means that TCP New Reno keeps track of the number of duplicate ACKs received during fast recovery and only reduces the cwnd by the number of new ACKs received (number of new packets acknowledged) beyond the original packet that triggered the fast recovery.
   - By doing this, TCP New Reno ensures a more precise recovery of the congestion window size, allowing it to resume normal congestion avoidance more accurately after the fast recovery phase.

3. **Fast Retransmit:**
   - TCP New Reno performs fast retransmit, just like TCP Reno, when it receives three duplicate ACKs indicating a packet loss.

4. **AIMD After Fast Recovery:**
   - After the fast recovery phase, TCP New Reno resumes congestion avoidance using the Additive Increase, Multiplicative Decrease (AIMD) approach.
   - It starts with the new value of cwnd after the fast recovery phase and increases cwnd more conservatively to probe for available bandwidth while avoiding congestion.

TCP New Reno's improvement over TCP Reno lies in its handling of multiple packet losses within a single window. By reducing the congestion window size more precisely during fast recovery, TCP New Reno can recover from congestion events more accurately and efficiently. This finer-grained recovery mechanism allows TCP New Reno to achieve better performance and higher throughput, particularly in scenarios with more challenging network conditions.

The primary difference between them lies in their handling of multiple packet losses within a single window of data.

   - TCP New Reno is an enhancement to TCP Reno, designed to improve its performance in scenarios with multiple packet losses within a single window of data.
   - During fast recovery, TCP New Reno reduces the congestion window size (cwnd) not by half, but by the number of new packets that have been acknowledged since entering the fast recovery state.
   - TCP New Reno keeps track of the number of duplicate ACKs received during fast recovery, and this count corresponds to the number of new packets acknowledged since the loss event. It reduces cwnd by this count, resulting in a more precise recovery of the congestion window size.
   - By allowing for more precise recovery, TCP New Reno can resume normal congestion avoidance more accurately after the fast recovery phase.

In summary, the main difference between TCP Reno and TCP New Reno is their handling of multiple packet losses during fast recovery. TCP Reno reduces cwnd by half regardless of the number of duplicate ACKs received, while TCP New Reno reduces cwnd by the number of new packets acknowledged since entering fast recovery, leading to a more refined recovery process.

TCP New Reno's improvement over TCP Reno enables it to handle multiple packet losses more efficiently and accurately, leading to better performance and higher throughput, especially in networks with more challenging conditions. As a result, TCP New Reno has become the de facto standard in modern TCP implementations, gradually replacing the original TCP Reno algorithm.

Here is some of the results of the simulation of TCP New Reno:

- New Reno with low packet loss rate and sshtresh = 65535
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/00d31ef3-b24c-4648-98d0-5396da0ad00e)


- New Reno with low packet loss rate and sshtresh = 256
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/d0ec562f-66fc-429d-bc15-65ecbe6f4a3f)


- New Reno with high packet loss rate and sshtresh = 65535
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/d32db59b-e881-4c08-88d5-670388bc8b58)


As we can see, when the packet loss rate is low, the congestion window size increases gradually and the throughput increases linearly. But when the packet loss rate is high, the congestion window size decreases rapidly and the throughput decreases linearly. So the overall performance of our connection gets worse by increasing the packet loss rate.

Also by decreasing ssthresh, we exit the slow start phase sooner and enter the congestion avoidance phase.


## TCP BBR

TCP BBR (Bottleneck Bandwidth and Round-trip time) is a modern congestion control algorithm developed by Google. It is designed to achieve high throughput and low latency by efficiently utilizing available network bandwidth and adapting to changing network conditions. TCP BBR uses a model-based approach to estimate the bottleneck bandwidth and round-trip time (RTT) of the network, allowing it to make informed decisions about the sending rate.

Here's how TCP BBR works in full detail:

1. **Bottleneck Bandwidth (BB) and Minimum RTT Estimation:**
   - Upon starting a TCP BBR connection, the algorithm begins by estimating the bottleneck bandwidth (BB) and minimum round-trip time (RTT) of the network path.
   - The BB is the capacity of the narrowest link (bottleneck link) in the network, and the minimum RTT represents the shortest round-trip time observed during the initial probing.

2. **Startup Phase:**
   - TCP BBR starts in the "Startup" phase, during which it quickly increases the sending rate to probe the network's capacity.
   - Initially, it sets the sending rate to one packet per RTT to build up the sending pipeline.
   - The algorithm then gradually increases the sending rate using an exponentially growing congestion window.

3. **Bottleneck Bandwidth Probing:**
   - During the Startup phase, TCP BBR probes the network to estimate the bottleneck bandwidth (BB) and the maximum amount of data that can be sent without causing undue congestion.
   - It monitors the number of packets delivered to the network and observes how the queue is filling up, which helps it estimate the available bandwidth.

4. **RTT and Delay Measurements:**
   - TCP BBR continuously measures the RTT and packet spacing to detect changes in network delay.
   - These measurements are used to update the model of the bottleneck bandwidth and adjust the sending rate to maintain optimal performance.

5. **Transition to ProbeBW Phase:**
   - Once TCP BBR detects that the bottleneck bandwidth has been reached or if there is a sudden increase in round-trip time (RTT), it switches from the Startup phase to the "ProbeBW" phase.
   - The ProbeBW phase aims to probe the available network bandwidth more aggressively.

6. **ProbeBW Phase:**
   - In the ProbeBW phase, TCP BBR attempts to send at a rate close to the estimated bottleneck bandwidth to explore the network's capacity fully.
   - It allows the sending rate to fluctuate based on real-time measurements of the bottleneck bandwidth and adjusts the congestion window accordingly.

7. **Drain Phase:**
   - After the ProbeBW phase, TCP BBR enters the "Drain" phase, where it backs off the sending rate significantly to reduce any residual queues and drain the network.

8. **Adaptive Rate Control:**
   - Throughout the connection's lifetime, TCP BBR uses adaptive rate control to adjust the sending rate based on real-time observations of the bottleneck bandwidth and RTT.
   - This adaptability allows TCP BBR to achieve high throughput while maintaining low latency and avoiding undue congestion.

TCP BBR's main advantage lies in its ability to accurately estimate the bottleneck bandwidth and RTT, allowing it to adapt to varying network conditions effectively. By efficiently utilizing available bandwidth and minimizing queuing delay, TCP BBR improves the overall performance and stability of TCP connections, especially in high-speed and long-distance networks. It has been widely adopted and is an essential component of modern TCP implementations.

Here is some of the results of the simulation of TCP BBR:

- BBR with estimated bandwidth of 512 and RTT per cycle of 10
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/3c758e30-e754-4bb6-8ff3-8a8fd415c561)

- BRR with estimated bandwidth of 315 and RTT per cycle of 13
![image](https://github.com/Hadi-loo/CN_CHomeworks4/assets/83643850/bced9196-3c00-4c69-8414-e7b0c7583643)


Overall, we can't always say that TCP BBR performs better than TCP RENO and TCP New Reno. While TCP BBR is a highly efficient and modern congestion control algorithm, it is not accurate to say that it always performs better than TCP Reno and TCP New Reno in every situation. The performance of these congestion control algorithms depends on various factors, including the network conditions, application requirements, and the specific use case. Let's consider some scenarios where each algorithm might excel:

1. **High-speed and Long-distance Networks:**
   - TCP BBR is designed to work particularly well in high-speed and long-distance networks. In such scenarios, where traditional TCP algorithms like Reno and New Reno might experience higher queuing delays, TCP BBR's ability to estimate the bottleneck bandwidth and adjust the sending rate based on the measured round-trip time can provide better throughput and lower latency.

2. **Low Bandwidth and Low Latency Networks:**
   - In some cases, TCP Reno or TCP New Reno might perform equally well or even better than TCP BBR. For example, in networks with very low bandwidth and low latency, the overhead of TCP BBR's complex model-based approach might not be as beneficial as in high-speed and long-distance networks.

3. **Network Stability and Congestion Level:**
   - TCP BBR's performance heavily depends on accurate measurements of the network's bottleneck bandwidth and RTT. In scenarios with highly dynamic and unstable network conditions, the accuracy of these measurements might be compromised, impacting TCP BBR's effectiveness. In contrast, TCP Reno and TCP New Reno have simpler mechanisms that can perform more robustly under certain conditions.

4. **Application Characteristics:**
   - The performance of congestion control algorithms can also be influenced by the specific characteristics of the application. Some applications might require low latency and responsive data delivery, while others might prioritize high throughput. Different algorithms may cater better to the specific needs of different applications.

Overall, TCP BBR is an excellent choice for optimizing throughput and latency in a wide range of network conditions, and it has been shown to perform very well in many real-world scenarios, especially in high-speed, long-distance networks. However, TCP Reno and TCP New Reno remain reliable and widely-used congestion control algorithms, and their performance should not be underestimated, especially in certain network environments or applications.

Ultimately, the choice of congestion control algorithm depends on the specific requirements and characteristics of the network, and it is essential to consider the factors mentioned above when deciding which algorithm to use in a particular scenario. Additionally, the ongoing development of new congestion control algorithms and improvements to existing ones may further impact the performance landscape in the future.


#### 6. Describing other congestion avoidance protocols and comparing them with algorithms that provided in this project:
- **Compound TCP**: Compound TCP (CTCP) is a congestion control algorithm developed by Microsoft for use in Windows operating systems. It is designed to optimize TCP performance in high-speed and high-delay networks. CTCP combines two congestion control algorithms: the traditional TCP Reno and the TCP Vegas.
- **TCP Hybla**: TCP Hybla is a congestion control algorithm developed by the Politecnico di Torino in Italy. It is designed to improve the performance of TCP in networks with high bandwidth and long round-trip times (RTTs). TCP Hybla aims to address the inherent limitations of traditional TCP Reno, which may experience poor throughput and excessive delay in such network conditions.
- **TCP Cubic**: CUBIC (Cubic Congestion Control) is a TCP congestion control algorithm designed to provide efficient and fair bandwidth utilization in modern networks. CUBIC aims to address the limitations of traditional TCP Reno congestion control, which can lead to suboptimal performance in high-speed, long-distance networks. CUBIC uses a different approach to determine the appropriate sending rate and congestion window size.Unlike Reno, which uses a linear growth pattern, CUBIC employs a cubic growth pattern for the congestion window. It allows for a more aggressive increase in the sending rate during the congestion avoidance phase, maximizing throughput and reducing latency.


TCP Cubic is works better than TCP Reno, New Reno, and BBR in terms of the needed convergence time to the maximum possible CWND size in the network. Contrary to other protocols, it uses a cubic function to calculate the size of the congestion window, which results in a more aggressive slope of raising the window size at low congestion times and a less aggressive slope at high congestion times.  







