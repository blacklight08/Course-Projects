`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:09:13 09/17/2013 
// Design Name: 
// Module Name:    MUX3 
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
module MUX5(
    output o1,
    output o2,
    output o3,
	 output o4,
	 output o5,
    input a1,
    input a2,
    input a3,
	 input a4,
	 input a5,
    input b1,
    input b2,
    input b3,
	 input b4,
	 input b5,
	 input enable
    );
MUX(o1,enable,a1,b1);
MUX(o2,enable,a2,b2);
MUX(o3,enable,a3,b3);
MUX(o4,enable,a4,b4);
MUX(o5,enable,a5,b5);
endmodule
