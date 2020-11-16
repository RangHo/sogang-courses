`timescale 1ns / 1ps

module four_bit_8421_decade_counter(clk, rst, q);
    input clk, rst;
    output [3:0] q;
    
    wire rst_combined;
    
    // 9(10) = 1001(2)
    assign rst_combined = rst | (q[3] & ~q[2] & ~q[1] & q[0]);

    jk_flip_flop jk0(.j(1), .k(1), .clk(clk), .rst(rst_combined), .q(q[0]), .nq());
    jk_flip_flop jk1(.j(q[0]), .k(q[0]), .clk(clk), .rst(rst_combined), .q(q[1]), .nq());
    jk_flip_flop jk2(.j(q[1] & q[0]), .k(q[1] & q[0]), .clk(clk), .rst(rst_combined), .q(q[2]), .nq());
    jk_flip_flop jk3(.j(q[2] & q[1] & q[0]), .k(q[2] & q[1] & q[0]), .clk(clk), .rst(rst_combined), .q(q[3]), .nq());

endmodule
