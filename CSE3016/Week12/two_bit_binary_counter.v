`timescale 1ns / 1ps

module two_bit_binary_counter(clk, rst, q);
    input clk, rst;
    output [1:0] q;

    jk_flip_flop jk0(.j(1), .k(1), .clk(clk), .rst(rst), .q(q[0]), .nq());
    jk_flip_flop jk1(.j(q[0]), .k(q[0]), .clk(clk), .rst(rst), .q(q[1]), .nq());

endmodule
