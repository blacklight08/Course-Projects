`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:05:11 10/29/2013 
// Design Name: 
// Module Name:    coke_vendor 
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
`include "Counter.v"
`include "CLA_Adder.v"
`include "Register_5_bit.v"
`include "Register_2_bit.v"
`include "Priority_encoder.v"
`include "MUX3.v"
module coke_vendor(
	input ten,
	input five,
	input two,
	input one,
	input slwclk,
	input O,
	output vended,
	output processing,
	output clk1
	
    ); 
	 wire clk,w,c,i1,i2,i3,i4,I1,I2,I3,I4,reset1,reset2,M5,M4,M3,M2,M1,sum1,sum2,sum3,sum4,sum5,sum6,
	 O1,O2,O3,O4,O4,O6,Oo,
	 sumf1,sumf2,sumf3,sumf4,sumf5,sumf6,sumi1,sumi2,sumi3,sumi4,sumi5,
	 fst2,fst1,ist2,ist1,xi,xo;
	 
	 assign Oo = 0;
	 
	 Counter(clk,Oo,slwclk);
	 
	 assign clk1 = clk;
	 
	 or(w,one,two,five,ten);
	 
	 Priority_encoder(i1,i2,i3,i4,one,two,five,ten);
	 
	 MUX5(I1,I2,I3,I4,xo,O,O,O,O,O,i1,i2,i3,i4,xi,reset1);
	 
	 Register_5_bit(M5,M4,M3,M2,M1,O,I1,I2,I3,I4,clk,O);
	 
	 CLA_Adder(sumf1,sumf2,sumf3,sumf4,sumf5,sumf6,M1,M2,M3,M4,M5,sumi1,sumi2,sumi3,sumi4,sumi5,O);
	 
	 MUX5(sum1,sum2,sum3,sum4,sum5,O,O,O,O,O,sumf1,sumf2,sumf3,sumf4,sumf5,reset2);
	 
	 Register_5_bit(sumi5,sumi4,sumi3,sumi2,sumi1,sum5,sum4,sum3,sum2,sum1,clk,O);

	 CLA_Adder(O1,O2,O3,O4,O5,O6,O,O,~O,O,~O,sumf1,sumf2,sumf3,sumf4,sumf5,~O);
	 
	 Register_2_bit(fst2,fst1,ist2,ist1,clk,O);
	 
	 assign c = ((~O5)&(~O4)&(~O3)&(~O2)&(~O1)) | ((~O6)&(O5));
	 
	 assign ist2 = (fst1 & ((~fst2 & ~c) | (fst2&(~w))));
	 
	 assign ist1 = (fst1 & (fst2 | (~c)) ) | (~fst2 & ~fst1 & w);
	 
	 assign reset1 = ((~w)&(fst1 | ~fst2)) | (~fst2 & fst1);
	 
	 assign reset2 = (~fst2 & fst1 & c) | (~fst2 & ~fst1 & ~w);
	 
	 assign processing = (~fst2 & fst1 & ~c);
	 
	 assign vended =  (~fst2) & (fst1) & c;
	 
	 endmodule
	 