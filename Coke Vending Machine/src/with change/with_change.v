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
`include "Demux.v"
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
	 
	 wire g5_4,g5_3,g5_2,g5_1,g5_0,a5_4,a5_3,a5_2,a5_1,a5_0,a5_5,
			g2_4,g2_3,g2_2,g2_1,g2_0,a2_4,a2_3,a2_2,a2_1,a2_0,a2_5,
			g1_4,g1_3,g1_2,g1_1,g1_0,a1_4,a1_3,a1_2,a1_1,a1_0,a1_5,
			g10_4,g10_3,g10_2,g10_1,g10_0,a10_4,a10_3,a10_2,a10_1,a10_0,a10_5;
			
	 wire i5_4,i5_3,i5_2,i5_1,i5_0,b5_4,b5_3,b5_2,b5_1,b5_0,b5_5,
			i2_4,i2_3,i2_2,i2_1,i2_0,b2_4,b2_3,b2_2,b2_1,b2_0,b2_5,
			i1_4,i1_3,i1_2,i1_1,i1_0,b1_4,b1_3,b1_2,b1_1,b1_0,b1_5,
			i10_4,i10_3,i10_2,i10_1,i10_0,b10_4,b10_3,b10_2,b10_1,b10_0,b10_5;
			
	 wire m_4,m_3,m_2,m_1,m_0,
			t_4,t_3,t_2,t_1,t_0,
			s_4,s_3,s_2,s_1,s_0,s_5,
			r_4,r_3,r_2,r_1,r_0;
			
	 wire mt1_4,mt1_3,mt1_2,mt1_1,mt1_0,
			mt2_4,mt2_3,mt2_2,mt2_1,mt2_0,
			mt3_4,mt3_3,mt3_2,mt3_1,mt3_0,
			mt4_4,mt4_3,mt4_2,mt4_1,mt4_0,
			t5_4,t5_3,t5_2,t5_1,t5_0,
			t2_4,t2_3,t2_2,t2_1,t2_0,
			t1_4,t1_3,t1_2,t1_1,t1_0,
			SEL_1,SEL_2,SEL_3;
			
	 wire x5,x2,x1,
			y5,y2,y_2,y1,y_1,d;
			
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
	 
	 
	 //Amount given by user
	 MUX5 M_T (m_4,m_3,m_2,m_1,m_0,sumf5,sumf4,sumf3,sumf2,sumf1,t_4,t_3,t_2,t_1,t_0,c); 
	 Register_5_bit Total (t_4,t_3,t_2,t_1,t_0,m_4,m_3,m_2,m_1,m_0,clk,O);
	 
	 //Amount retured to user
	 CLA_Adder (s_0,s_1,s_2,s_3,s_4,s_5,t_0,t_1,t_2,t_3,t_4,Oo,Oo,~Oo,Oo,~Oo,~Oo);
	 MUX5 M_T1(mt1_4,mt1_3,mt1_2,mt1_1,mt1_0,t5_4,t5_3,t5_2,t5_1,t5_0,t2_4,t2_3,t2_2,t2_1,t2_0,SEL_1);
	 MUX5 M_T2(mt2_4,mt2_3,mt2_2,mt2_1,mt2_0,t1_4,t1_3,t1_2,t1_1,t1_0,r_4,r_3,r_2,r_1,r_0,SEL_1);
	 MUX5 M_T3(mt3_4,mt3_3,mt3_2,mt3_1,mt3_0,mt1_4,mt1_3,mt1_2,mt1_1,mt1_0,mt2_4,mt2_3,mt2_2,mt2_1,mt2_0,SEL_2);
	 MUX5 M_T4(mt4_4,mt4_3,mt4_2,mt4_1,mt4_0,mt3_4,mt3_3,mt3_2,mt3_1,mt3_0,s_0,s_1,s_2,s_3,s_4,SEL_3);
	 Register_5_bit Change (r_4,r_3,r_2,r_1,r_0,mt4_4,mt4_3,mt4_2,mt4_1,mt4_0,O);
	 
	 
	 //Given money by user
	 Register_5_bit G5 (g5_4,g5_3,g5_2,g5_1,g5_0,a5_4,a5_3,a5_2,a5_1,a5_0,clk,O);
	 CLA_Adder A_G5 (a5_0,a5_1,a5_2,a5_3,a5_4,a5_5,five,Oo,Oo,Oo,Oo,g5_0,g5_1,g5_2,g5_3,g5_4,Oo);
	 
	 Register_5_bit G2 (g2_4,g2_3,g2_2,g2_1,g2_0,a2_4,a2_3,a2_2,a2_1,a2_0,clk,O);
	 CLA_Adder A_G2 (a2_0,a2_1,a2_2,a2_3,a2_4,a2_5,two,Oo,Oo,Oo,Oo,g2_0,g2_1,g2_2,g2_3,g2_4,Oo);
	 
	 Register_5_bit G1 (g1_4,g1_3,g1_2,g1_1,g1_0,a1_4,a1_3,a1_2,a1_1,a1_0,clk,O);
	 CLA_Adder A_G1 (a1_0,a1_1,a1_2,a1_3,a1_4,a1_5,one,Oo,Oo,Oo,Oo,g1_0,g1_1,g1_2,g1_3,g1_4,Oo);
	 
	 Register_5_bit G10 (g10_4,g10_3,g10_2,g10_1,g10_0,a10_4,a10_3,a10_2,a10_1,a10_0,clk,O);
	 CLA_Adder A_G10 (a10_0,a10_1,a10_2,a10_3,a10_4,a10_5,five,Oo,Oo,Oo,Oo,g10_0,g10_1,g10_2,g10_3,g10_4,Oo);
	 
	 
	// Money in the vending Machine (duped)
	 Register_5_bit IR5 (i5_4,i5_3,i5_2,i5_1,i5_0,b5_4,b5_3,b5_2,b5_1,b5_0,clk,O);
	 CLA_Adder A_I5 (b5_0,b5_1,b5_2,b5_3,b5_4,b5_5,one,Oo,Oo,Oo,Oo,i5_0,i5_1,i5_2,i5_3,i5_4,~Oo);
	 
	 Register_5_bit IR2 (i2_4,i2_3,i2_2,i2_1,i2_0,b2_4,b2_3,b2_2,b2_1,b2_0,clk,O);
	 CLA_Adder A_I2 (b2_0,b2_1,b2_2,b2_3,b2_4,b2_5,one,Oo,Oo,Oo,Oo,i2_0,i2_1,i2_2,i2_3,i2_4,~Oo);
	 
	 Register_5_bit IR1 (i1_4,i1_3,i1_2,i1_1,i1_0,b1_4,b1_3,b1_2,b1_1,b1_0,clk,O);
	 CLA_Adder A_I1 (b1_0,b1_1,b1_2,b1_3,b1_4,b1_5,one,Oo,Oo,Oo,Oo,g1_0,i1_1,i1_2,i1_3,i1_4,~Oo);
	 
	 Register_5_bit IR10 (i10_4,i10_3,i10_2,i10_1,i10_0,b10_4,b10_3,b10_2,b10_1,b10_0,clk,O);
	 CLA_Adder A_I10 (b10_0,b10_1,b10_2,b10_3,b10_4,b10_5,one,Oo,Oo,Oo,Oo,i10_0,i10_1,i10_2,i10_3,i10_4,~Oo);
	 
	 //Determination logic
	 CLA_Adder (t5_0,t5_1,t5_2,t5_3,t5_4,t5_5,r_1,r_2,r_3,r_4,r_5,~Oo,Oo,~Oo,Oo,Oo,~Oo);
	 CLA_Adder (t2_0,t2_1,t2_2,t2_3,t2_4,t2_5,r_1,r_2,r_3,r_4,r_5,Oo,~Oo,Oo,Oo,Oo,~Oo);
	 CLA_Adder (t1_0,t1_1,t1_2,t1_3,t1_4,t1_5,r_1,r_2,r_3,r_4,r_5,~Oo,Oo,Oo,Oo,Oo,~Oo);
	 assign x5 = t5_4;
	 assign x2 = t2_4;
	 assign x1 = t1_4;
	 Demux D5 (y5,y_2,~O,~x5);
	 Demux D2 (y2,y_1,y_2,~x2);
	 Demux D1 (y1,d,y_1,~x1);
	 assign sel_5 = (~i5_4) & (~i5_3) & (~i5_2) & (~i5_1) & (~i5_0); 
	 assign SEL_1 = ~x5;
	 assign SEL_3 = ~x5;
	 endmodule
