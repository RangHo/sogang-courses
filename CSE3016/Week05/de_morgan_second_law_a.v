`timescale 1ns / 1ps

module de_morgan_second_law_a(a, b, c);
    input a, b;
    output c;
    
    assign c = ~(a & b);

endmodule
