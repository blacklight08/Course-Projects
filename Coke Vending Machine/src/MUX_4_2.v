`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:40:18 09/26/2013 
// Design Name: 
// Module Name:    MUX_4_2 
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
////////////////////////////////////////////////////////////////////////////////
`include "MUX.v"
module MUX_4_2(
    output O,
    input S1,
    input S2,
    input a,
    input b,
    input c,
    input d
    );
wire w1,w2;
MUX(w1,S1,a,b);//0,0 passes d
MUX(w2,S1,c,d);//1,0 passes c
MUX(O,S2,w1,w2);

endmodule
