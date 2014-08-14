`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:17:14 09/17/2013 
// Design Name: 
// Module Name:    Priority_encoder 
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
`include "MUX4.v"
module Priority_encoder(
    output o1,
	 output o2,
	 output o3,
	 output o4,
    input one,
    input two,
    input five,
    input ten
    );
wire w0,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12;
assign w0=0;
MUX4(w1,w2,w3,w4,w0,w0,w0,~w0,w0,w0,w0,w0,one);
MUX4(w5,w6,w7,w8,w0,w0,~w0,w0,w1,w2,w3,w4,two);
MUX4(w9,w10,w11,w12,w0,~w0,w0,~w0,w5,w6,w7,w8,five);
MUX4(o1,o2,o3,o4,~w0,w0,~w0,w0,w9,w10,w11,w12,ten);

endmodule
