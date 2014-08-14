`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:29:55 11/01/2013 
// Design Name: 
// Module Name:    Register_2_bit 
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
module Register_2_bit(
    output O1,
    output O2,
    input I1,
    input I2,
    input clk,
    input reset
    );
Flip_Flop(O1,I1,clk,reset);
Flip_Flop(O2,I2,clk,reset);

endmodule
