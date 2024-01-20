# Create a new ns (Network Simulator) object
set simulator [new Simulator]

# Define color classes for visualizing traffic sources in NAM (Network Animator)
$simulator color 0 blue
$simulator color 1 red

# Create a NAM file for visualization and associate it with the simulator object
set namFile [open out.nam w]
$simulator namtrace-all $namFile

# Procedure to finish simulation, flush traces, close NAM file, and visualize network using NAM
proc finish {} {
    global simulator namFile
    $simulator flush-trace
    close $namFile
    exec nam out.nam &
    exit 0
}

# Define nodes in the network
set node0 [$simulator node]
set node1 [$simulator node]
set node2 [$simulator node]
set node3 [$simulator node]

# Create duplex links between nodes with specified bandwidth, delay, and DropTail queue
$simulator duplex-link $node2 $node3 1.7Mb 20ms DropTail

$simulator duplex-link $node0 $node2 2Mb 10ms DropTail 
$simulator duplex-link $node1 $node2 2Mb 10ms DropTail

# Set queue limits for each link
$simulator queue-limit $node2 $node3 10
$simulator queue-limit $node0 $node2 10
$simulator queue-limit $node1 $node2 10

# Set link orientations for proper visualization in NAM
$simulator duplex-link-op $node2 $node0 orient left-up 
$simulator duplex-link-op $node2 $node3 orient right
$simulator duplex-link-op $node2 $node1 orient left-down 

# Set the angle of the queue display between nodes
$simulator duplex-link-op $node0 $node2 queuePos 0.5
$simulator duplex-link-op $node2 $node3 queuePos 0.5
$simulator duplex-link-op $node1 $node2 queuePos 0.5

# Create TCP and UDP agents, and attach them to nodes
set udpAgent0 [new Agent/UDP]
set nullAgent0 [new Agent/Null]
$simulator attach-agent $node0 $udpAgent0
$simulator attach-agent $node3 $nullAgent0
$simulator connect $udpAgent0 $nullAgent0

set tcpAgent0 [new Agent/TCP]
set tcpSink0 [new Agent/TCPSink]
$simulator attach-agent $node1 $tcpAgent0
$simulator attach-agent $node3 $tcpSink0
$simulator connect $tcpAgent0 $tcpSink0

# Create a CBR traffic application, set packet size and interval, and attach it to the UDP agent
set cbrApp0 [new Application/Traffic/CBR]
$cbrApp0 set packetSize_ 1000 ;# in Bytes
$cbrApp0 set interval_ 0.01 ;# one packet in each 0.005 seconds
$cbrApp0 attach-agent $udpAgent0

# Create an FTP application and attach it to the TCP agent
set ftpApp1 [new Application/FTP]
$ftpApp1 attach-agent $tcpAgent0


# Set flow IDs for agents
$tcpAgent0 set fid_ 0
$udpAgent0 set fid_ 1

# Schedule events for starting and stopping applications
$simulator at 0.5 "$ftpApp1 start"
$simulator at 1.0 "$cbrApp0 start"
$simulator at 4.0 "$ftpApp1 stop"
$simulator at 4.5 "$cbrApp0 stop"

$simulator at 5.0 "finish"

# Run the simulation
$simulator run