`timescale 1ns / 1ps

module four_bit_up_down_counter(clk, rst, down, q);
    input clk, rst, down;
    output [3:0] q;

    wire [3:0] nq;

    jk_flip_flop jk0(
        .j(1),
        .k(1),
        .clk(clk),
        .rst(rst),
        .q(q[0]),
        .nq(nq[0])
    );
    jk_flip_flop jk1(
        .j((~down & q[0]) | (down & nq[0])),
        .k((~down & q[0]) | (down & nq[0])),
        .clk(clk),
        .rst(rst),
        .q(q[1]),
        .nq(nq[1])
    );
    jk_flip_flop jk2(
        .j((~down & q[1] & q[0]) | (down & nq[1] & nq[0])),
        .k((~down & q[1] & q[0]) | (down & nq[1] & nq[0])),
        .clk(clk),
        .rst(rst),
        .q(q[2]),
        .nq(nq[2])
    );
    jk_flip_flop jk3(
        .j((~down & q[2] & q[1] & q[0]) | (down & nq[2] & nq[1] & nq[0])),
        .k((~down & q[2] & q[1] & q[0]) | (down & nq[2] & nq[1] & nq[0])),
        .clk(clk),
        .rst(rst),
        .q(q[3]),
        .nq(nq[3])
    );

endmodule
