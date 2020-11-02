`timescale 1ns / 1ps

module bcd_adder(a0, a1, a2, a3, b0, b1, b2, b3, cin, c1, c2, c3, c4, s0, s1, s2, s3, bcd0, bcd1, bcd2, bcd3, cout);
    input a0, a1, a2, a3, b0, b1, b2, b3, cin;
    output c1, c2, c3, c4, s0, s1, s2, s3, bcd0, bcd1, bcd2, bcd3, cout;
    
    four_bit_parallel_adder adder(
        .a0(a0), .a1(a1), .a2(a2), .a3(a3),
        .b0(b0), .b1(b1), .b2(b2), .b3(b3),
        .cin(cin), .c1(c1), .c2(c2), .c3(c3), .c4(c4),
        .s0(s0), .s1(s1), .s2(s2), .s3(s3)
    );
    
    assign cout = c4 | (s2 & s3) | (s3 & s1);
    assign bcd0 = s0;
    assign bcd1 = s1 ^ cout;
    assign bcd2 = s2 ^ cout ^ (s1 & cout);
    assign bcd3 = s3 ^ ((s2 & cout) | ((s1 & cout) & (s2 ^ cout)));
endmodule
