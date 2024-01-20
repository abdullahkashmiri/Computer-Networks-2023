
#21L7512 ABDULLAH DAR BSCS 5G1 lab no Q2
#Q2- STAR TOPOLOGY

set simulator [new Simulator]

$simulator color 1 blue
$simulator color 2 red

$simulator rtproto DV
set nsf [open out.nam w]
$simulator namtrace-all $nsf

proc finish {} {
        global simulator nsf
        $simulator flush-trace
        close $nsf
        exec nam out.nam
        exit 0
        }

#Making Nodes        
for {set i 0} {$i<7} {incr i} {
set n($i) [$simulator node]
}

#Making Links
for {set i 1} {$i<7} {incr i} {
$simulator duplex-link $n(0) $n($i) 512Kb 10ms SFQ
}

#Orienting nodes
$simulator duplex-link-op $n(0) $n(1) orient left-up
$simulator duplex-link-op $n(0) $n(2) orient right-up
$simulator duplex-link-op $n(0) $n(3) orient right
$simulator duplex-link-op $n(0) $n(4) orient right-down
$simulator duplex-link-op $n(0) $n(5) orient left-down
$simulator duplex-link-op $n(0) $n(6) orient left

#UDP  connection
set udp [new Agent/UDP]
$udp set class_ 2
$simulator attach-agent $n(2) $udp

set null [new Agent/Null]
$simulator attach-agent $n(5) $null

$simulator connect $udp $null

#TCP connection
set tcp [new Agent/TCP]
$tcp set class_ 1
$simulator attach-agent $n(1) $tcp

set sink [new Agent/TCPSink]
$simulator attach-agent $n(4) $sink

$simulator connect $tcp $sink

#FTP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp

#CBR connection
set cbr [new Application/Traffic/CBR]
$cbr set rate_ 256Kb
$cbr attach-agent $udp

#setting timings
$simulator rtmodel-at 0.5 down $n(0) $n(5)
$simulator rtmodel-at 0.9 up $n(0) $n(5)

$simulator rtmodel-at 0.7 down $n(0) $n(4)
$simulator rtmodel-at 1.2 up $n(0) $n(4)

$simulator at 0.1 "$ftp start"
$simulator at 1.5 "$ftp stop"

$simulator at 0.2 "$cbr start"
$simulator at 1.3 "$cbr stop"

$simulator at 2.0 "finish"
$simulator run