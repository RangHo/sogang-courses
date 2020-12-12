`timescale 1ns / 1ps

module four_bit_ring_counter(clk, out);
    input clk;
    output [3:0] out;

    wire [3:0] in;
    reg first;

    initial first = 1;

    always @(posedge clk)
        if (first)
            first = 0;

        assign in[0] = first | out[3];
        assign in[1] = 0 | out[0];
        assign in[2] = 0 | out[1];
        assign in[3] = 0 | out[2];

        d_flip_flop d1(.d(in[0]), .clk(clk), .q(out[0]), .nq());
        d_flip_flop d2(.d(in[1]), .clk(clk), .q(out[1]), .nq());
        d_flip_flop d3(.d(in[2]), .clk(clk), .q(out[2]), .nq());
        d_flip_flop d4(.d(in[3]), .clk(clk), .q(out[3]), .nq());
endmodule

