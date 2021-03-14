`timescale 1ns / 1ps

module crumb_comparator(a, b, c, d, gt, eq, lt);
    input a, b, c, d;
    output gt, eq, lt;
    
    assign gt = (a & ~c) | (b & ~c & ~d) | (a & b & ~d);
    assign eq = ~(a ^ c) & ~(b ^ d);
    assign lt = (~a & c) | (~a & ~b & d) | (~b & c & d);

endmodule
