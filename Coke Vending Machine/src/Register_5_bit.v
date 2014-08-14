`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:13:46 10/22/2013 
// Design Name: 
// Module Name:    Register_4_bit 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
`include "Flip_Flop.v"
module Register_5_bit(
    output O1,
    output O2,
    output O3,
    output O4,
	 output O5,
    input I1,
    input I2,
    input I3,
    input I4,
	 input I5,
    input clk,
	 input reset
    );
Flip_Flop(O1,I1,clk,reset);
Flip_Flop(O2,I2,clk,reset);
Flip_Flop(O3,I3,clk,reset);
Flip_Flop(O4,I4,clk,reset);
Flip_Flop(O5,I5,clk,reset);
endmodule
