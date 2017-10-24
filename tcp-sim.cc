#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/bulk-send-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TcpBulkSendExample");

int main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);


  NodeContainer node,serverNode;
  serverNode.Create (1);
  node.Create (1);


  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices = pointToPoint.Install (serverNode.Get (0),node.Get (0));

  InternetStackHelper stack;
  stack.Install (serverNode);
  stack.Install (node);

  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (devices);

  Address sourceAddress(InetSocketAddress (i.GetAddress (0),50000));

  BulkSendHelper sourceHelper ("ns3::TcpSocketFactory",sourceAddress);
  sourceHelper.SetAttribute ("MaxBytes", UintegerValue (0));
  ApplicationContainer sourceApp = sourceHelper.Install(serverNode);
  sourceApp.Start (Seconds(1.0));
  sourceApp.Stop (Seconds(10.0));


  OnOffHelper clientHelper ("ns3::TcpSocketFactory",Address());
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpNewReno"));
  TypeId tid = TypeId::LookupByName ("ns3::TcpNewReno");
  Config::Set ("/NodeList/*/$ns3::TcpL4Protocol/SocketType", TypeIdValue (tid));
  //Config::Set ("/NodeList/"+ node.Get(0)->GetId() +"/$ns3::TcpL4Protocol/SocketType", TypeIdValue (tid));
  Ptr<Socket> clientSocket = Socket::CreateSocket(node.Get (0), TcpSocketFactory::GetTypeId ());
  clientSocket->Connect (sourceAddress); //There is a SIGSEGV i.e. segmentation fault here, no clue what i should do
  int j=0;
  Ptr<Packet> receivedPacket;
  do
  {
    j++;
    receivedPacket = clientSocket->Recv ();
    NS_LOG_DEBUG("Number of packets received:"+j);

  }while(!receivedPacket);

    /*
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
NOTE: I'm not sure if i should install internet stack on client node ie. node
      ClientSocket created in node->Get(0) (client node) can use .Connect() to connect to server, TCP handshake is supposed to happen here.
      So does it mean i should install the internetstack on client node as well?

      Objective:
      1.Create a TCP server
      2.Connect to it using TCP Socket (Here it self it gives SIGSEGV)
      3.Recieve packets from TCP server

      I'm way too afraid to compile this code :D as I couldn't take help from a TA in lab.
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
  */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  pointToPoint.EnablePcapAll("tcp_send",false);
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

/*

  devices = pointToPoint.Install (nodes);
  NodeContainer nodes;
  nodes.Create (2);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

*/
