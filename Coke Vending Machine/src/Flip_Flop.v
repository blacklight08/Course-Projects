`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:53:35 10/22/2013 
// Design Name: 
// Module Name:    Flip_Flop 
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
module Flip_Flop(
    output Q,
    input D,
    input clk,
	 input reset
    );
reg Q;
always @ ( posedge clk )
begin
	if(reset == 1'b1)
	Q=1'b0;
	else
	Q=D;
end
endmodule
