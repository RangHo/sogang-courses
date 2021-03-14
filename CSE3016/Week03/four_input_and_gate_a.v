`timescale 1ns / 1ps

module four_input_and_gate_a(a, b, c, d, e);
    input a, b, c, d;
    output e;

    assign e = a & b & c & d;

endmodule
