`timescale 1ns / 1ps

module even_parity_generator(a, b, c, d, e);
    input a, b, c, d;
    output e;
    
    assign e = a ^ b ^ c ^ d;

endmodule
