#21L7512 ABDULLAH DAR BSCS 5G1 lab no Q1
#Q1- RING TOPOLOGY

#Making Simulator
set simulator [new Simulator]
$simulator  rtproto DV

set nsf [open out.nam w]
$simulator  namtrace-all $nsf

proc finish {} {
        global simulator  nsf
        $simulator  flush-trace
        close $nsf
        exec nam out.nam
        exit 0
        }


#Making nodes
for {set i 0} {$i<7} {incr i} {
set n($i) [$simulator  node]
}


#Making links
for {set i 0} {$i<7} {incr i} {
$simulator  duplex-link $n($i) $n([expr ($i+1)%7]) 512Kb 5ms DropTail
}

$simulator  duplex-link-op $n(0) $n(1) queuePos 1
$simulator  duplex-link-op $n(0) $n(6) queuePos 1

#Making udp agent and attching to node 0
set udp [new Agent/UDP]
$simulator  attach-agent $n(0) $udp


#Making Null agent and attaching to node 3
set null [new Agent/Null]
$simulator  attach-agent $n(3) $null
$simulator  connect $udp $null

#CBR agent
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 1024
$cbr set interval_ 0.01
$cbr attach-agent $udp

$simulator  rtmodel-at 0.4 down $n(2) $n(3)
$simulator  rtmodel-at 1.0 up $n(2) $n(3)

$simulator  at 0.01 "$cbr start"
$simulator  at 1.5 "$cbr stop"

$simulator  at 2.0 "finish"
$simulator  run