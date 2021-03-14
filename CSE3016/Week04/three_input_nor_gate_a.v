`timescale 1ns / 1ps

module three_input_nor_gate_a(a, b, c, d);
    input a, b, c;
    output d;

    assign d = ~(a | b | c);

endmodule
