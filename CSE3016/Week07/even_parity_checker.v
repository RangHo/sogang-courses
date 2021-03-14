`timescale 1ns / 1ps

module even_parity_checker(a, b, c, d, p, pec);
    input a, b, c, d, p;
    output pec;
    
    assign pec = a ^ b ^ c ^ d ^ p;

endmodule
