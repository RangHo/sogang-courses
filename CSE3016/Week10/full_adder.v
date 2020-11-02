`timescale 1ns / 1ps

module full_adder(a, b, cin, s, cout);
    input a, b, cin;
    output s, cout;
    
    assign s = a ^ b ^ cin;
    assign cout = (a & b) | (cin & (a ^ b));
endmodule
