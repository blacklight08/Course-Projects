There are 11 included verilog files along with the main file 'coke_vendor.v'.

Counter.v : Basically a 28 bit counter whose most significant bit works as a clock with frequency 0.25 Hz. (The board works on 100000000Hz frequency).

Demux.v : Simple 1:2 demux with a single select line.
Flipflop.v : Basic flipflop code.
Mux.v : Simple 2:1 mux with one select line.

Mux4.v : Four 2:1 muxes with same select acts as mux with 4-bit bus as input
Mux3.v : Five 2:1 muxes with same select acts as mux with 5-bit bus as input

Mux_4_2.v : 4:1 mux with 2 select lines.

Priotity_encoder.v : Considers only 1 input of different coins and changes one-hot to binary

Register_2_bit.v : 2 flipflops
Register_5_bit.v

CLA_Adder.v : Both adder and subtractor for 5bits whose decimal value doesnt exceed 29 (so 6th carry not needed).
