`timescale 1ns / 1ps

module de_morgan_second_law_b(a, b, c);
    input a, b;
    output c;
    
    assign c = ~a | ~b;

endmodule
