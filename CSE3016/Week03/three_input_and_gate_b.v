`timescale 1ns / 1ps

module three_input_and_gate_b(a, b, c, d, e);
    input a, b, c;
    output d, e;

    assign d = a & b;
    assign e = d & c;

endmodule
