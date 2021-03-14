`timescale 1ns / 1ps

module half_adder_tb;

    reg a, b;
    wire s, c;
    half_adder DUT (
        .a(a),
        .b(b),
        .s(s),
        .c(c)
    );

    initial begin
        a = 0;
        b = 0;
        #20;

        a = 0;
        b = 1;
        #20;

        a = 1;
        b = 0;
        #20;

        a = 1;
        b = 1;
        #20;

        $finish;
    end

endmodule