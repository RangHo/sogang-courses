`timescale 1ns / 1ps

module bit_comparator(a, b, eq, neq, gt, lt);
    input a, b;
    output eq, neq, gt, lt;

    assign eq = ~(a ^ b);
    assign neq = a ^ b;
    assign gt = a & ~b;
    assign lt = ~a & b;

endmodule
