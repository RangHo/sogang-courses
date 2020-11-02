`timescale 1ns / 1ps

module four_bit_parallel_subtractor(a0, a1, a2, a3, b0, b1, b2, b3, cin, c1, c2, c3, c4, s0, s1, s2, s3);
    input a0, a1, a2, a3, b0, b1, b2, b3, cin;
    output c1, c2, c3, c4, s0, s1, s2, s3;
    
    full_adder f0(.a(a0), .b((b0 ^ cin)), .cin(cin), .s(s0), .cout(c1));
    full_adder f1(.a(a1), .b((b1 ^ cin)), .cin(c1), .s(s1), .cout(c2));
    full_adder f2(.a(a2), .b((b2 ^ cin)), .cin(c2), .s(s2), .cout(c3));
    full_adder f3(.a(a3), .b((b3 ^ cin)), .cin(c3), .s(s3), .cout(c4));
endmodule
