`timescale 1ns / 1ps

module four_bit_2421_decade_counter(clk, rst, q);
    input clk, rst;
    output [3:0] q;
    
    wire jump_flag;
    
    // Jump when q is 4
    assign jump_flag = ~q[3] & q[2] & ~q[1] & ~q[0];

    jk_flip_flop jk0(.j(1), .k(~jump_flag), .clk(clk), .rst(rst), .q(q[0]), .nq());
    jk_flip_flop jk1(.j(jump_flag | q[0]), .k(~jump_flag & q[0]), .clk(clk), .rst(rst), .q(q[1]), .nq());
    jk_flip_flop jk2(.j(~jump_flag & q[1] & q[0]), .k(jump_flag | q[1] & q[0]), .clk(clk), .rst(rst), .q(q[2]), .nq());
    jk_flip_flop jk3(.j(jump_flag | (q[2] & q[1] & q[0])), .k(~jump_flag & (q[2] & q[1] & q[0])), .clk(clk), .rst(rst), .q(q[3]), .nq());
endmodule
