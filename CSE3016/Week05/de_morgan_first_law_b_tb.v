`timescale 1ns / 1ps

module de_morgan_first_law_b_tb;

    reg a, b;
    wire c;
    de_morgan_first_law_b DUT (
        .a(a),
        .b(b),
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