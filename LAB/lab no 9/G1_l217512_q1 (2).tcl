set valid_input 0

puts "Enter a number greater than 4:"
set input [gets stdin]

if {$input % 2 == 0} {
    puts "Even integers from 4 to $input:"
    for {set i 4} {$i <= $input} {incr i} {
        puts $i
        incr i
    }
} else {
    puts "Odd integers from 3 to $input:"
    for {set i 3} {$i <= $input} {incr i} {
        puts $i
        incr i
    }
}

