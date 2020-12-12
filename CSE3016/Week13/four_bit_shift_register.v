`timescale 1ns / 1ps

module four_bit_shift_register(clk, in, out);
    input clk, in;
    output [3:0] out;

    d_flip_flop d1(.d(in), .clk(clk), .q(out[0]), .nq());
    d_flip_flop d2(.d(out[0]), .clk(clk), .q(out[1]), .nq());
    d_flip_flop d3(.d(out[1]), .clk(clk), .q(out[2]), .nq());
    d_flip_flop d4(.d(out[2]), .clk(clk), .q(out[3]), .nq());
endmodule
