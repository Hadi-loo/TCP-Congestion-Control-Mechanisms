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
