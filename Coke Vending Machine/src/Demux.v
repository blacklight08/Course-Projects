`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:26:40 11/22/2013 
// Design Name: 
// Module Name:    Demux 
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
module Demux(
    output O1,
    output O2,
    input I,
    input sel
    );
	 
	 assign O1 = I & sel;
	 assign O2 = I & ~sel;


endmodule
