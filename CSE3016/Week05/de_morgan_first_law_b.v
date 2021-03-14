`timescale 1ns / 1ps

module de_morgan_first_law_b(a, b, c);
    input a, b;
    output c;
    
    assign c = ~a & ~b;

endmodule
