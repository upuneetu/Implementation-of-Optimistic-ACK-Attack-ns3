# Implementation of Optimistic ACK attack on ns3

It involves optimisitcally sending ACK packets before the data is received. This may damage end-to-end reliability, but it can cause the sender to increase their congestion window (cwnd) size very fast and arbitrarily large. The premature ACKs will cause sender to assume the corresponding data has been received, even if it is still in flight. This attack is particularly dangerous because missing ACKs are TCP's signal for congestion. Optimistic ACKs can therefore mask this signal and cause serious network issues.



Contributors: 
* Puneet 15CO136
* Anishcharith 15CO108
* Rajesh 15CO138



## Instructions:

The example program is provided in the directory:   
``` scratch/optimisitc-ack-simulator.cc ```   
execute the following command to save the variation of congestion window with time in a csv file 
``` ./waf --run "scratch/optimisitc-ack-simulator --Opt-Ack = true --Save-CSV=true" ```

## References

* https://cseweb.ucsd.edu/~savage/papers/CCR99.pdf
* www.nsnam.org
