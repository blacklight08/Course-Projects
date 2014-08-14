`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:17:20 10/22/2013 
// Design Name: 
// Module Name:    Counter 
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
module Counter(
    output a,
    input reset ,
    input clk
    );
reg [27:0]Q;
always @ ( posedge clk )
begin
	if(reset == 1'b1)
	Q = 28'b00000000000000000000000000;
	else
		Q = Q+1;
	end
assign a = Q[27];
endmodule
