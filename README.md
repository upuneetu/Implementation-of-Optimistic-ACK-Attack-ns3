# Implementation of Optimistic ACK attack on ns3
It involves optimisitcally send ACK packets before the data is received. This may damage end-to-end reliability, but it can cause the sender to increase their congestion window (cwnd) size very fast and arbitrarily large. The premature ACKs will cause sender to assume the corresponding data has been received, even if it is still in flight. This attack is particularly dangerous because missing ACKs are TCP's signal for congestion. Optimistic ACKs can therefore mask this signal and cause serious network issues.

https://cseweb.ucsd.edu/~savage/papers/CCR99.pdf


Contributors: 
* Puneet 15CO136
* Anishcharith 15CO108
* Rajesh 15CO138

Result of Optimistic ACKing

![plot](https://github.com/pun97/Optimistic-ACKing-Attack/blob/master/plot.png)

#Instructions:

* Copy tcp-socket-base.cc and tcp-socket-base.h to ns3-dev-git or ns3allinone/src/internet/model/
* Copy example.cc to nse-dev-git or ns3allinone/scratch/
* Open terminal in ns3-dev-git or ns3allinone
* Run ./waf --run "scratch/example --Opt-Ack = true"
