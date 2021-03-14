`timescale 1ns / 1ps

module boolean_function_1(a, b, c, a_out, b_out);
    input a, b, c;
    output a_out, b_out;
    
    assign a_out = (~a | ~b) & ~c;
    assign b_out = ~((a & b) | c);

endmodule
