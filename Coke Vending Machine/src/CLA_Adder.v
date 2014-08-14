`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:01:25 09/24/2013 
// Design Name: 
// Module Name:    CLA_Adder 
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
`include "MUX_4_2.v"
module CLA_Adder(
    output O1,
    output O2,
    output O3,
    output O4,
    output O5,
	 output O6,
    input a0,
    input a1,
    input a2,
    input a3,
	 input a4,
    input b0,
    input b1,
    input b2,
    input b3,
	 input b4,
	 input Cin
    );
wire w1,w2,w3,w4,w5,w6,w7,w8,w9,w10;
assign z=0;
xor(w5,Cin,b0);
xor(w6,Cin,b1);
xor(w7,Cin,b2);
xor(w8,Cin,b3);
xor(w9,Cin,b4);
MUX_4_2(w1,a0,w5,~z,Cin,Cin,z);
MUX_4_2(w2,a1,w6,~z,w1,w1,z);
MUX_4_2(w3,a2,w7,~z,w2,w2,z);
MUX_4_2(w4,a3,w8,~z,w3,w3,z);
MUX_4_2(w10,a4,w9,~z,w4,w4,z);
xor(O1,a0,w5,Cin);
xor(O2,a1,w6,w1);
xor(O3,a2,w7,w2);
xor(O4,a3,w8,w3);
xor(O5,a4,w9,w4);
assign O6=w10;
endmodule