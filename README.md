# Optimistic-ACKing-Attack
Implementation of an attack on a system which uses TCP at its transport layer by sending ACKs before the data is received.

https://cseweb.ucsd.edu/~savage/papers/CCR99.pdf


Contributors: 
* Puneet 15CO136
* Anishcharith 15CO108
* Rajesh 15CO138

Reasult of Optimistic ACKing

![plot](https://github.com/pun97/Optimistic-ACKing-Attack/blob/master/plot.png)

#Instructions:

* Copy tcp-socket-base.cc and tcp-socket-base.h to ns3-dev-git or ns3allinone/src/internet/model/
* Copy example.cc to nse-dev-git or ns3allinone/scratch/
* Open terminal in ns3-dev-git or ns3allinone
* Run ./waf --run "scratch/example --Opt-Ack = true"
