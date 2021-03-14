`timescale 1ns / 1ps

module boolean_function_1_tb;

    reg a, b, c;
    wire d, e;
    boolean_function_1 DUT (
        .a(a),
        .b(b),
        .c(c),
        .a_out(d),
        .b_out(e)
    );

    initial begin
        a = 0;
        b = 0;
        c = 0;
        #20;

        a = 0;
        b = 0;
        c = 1;
        #20;

        a = 0;
        b = 1;
        c = 0;
        #20;

        a = 0;
        b = 1;
        c = 1;
        #20;

        a = 1;
        b = 0;
        c = 0;
        #20;

        a = 1;
        b = 0;
        c = 1;
        #20;

        a = 1;
        b = 1;
        c = 0;
        #20;

        a = 1;
        b = 1;
        c = 1;
        #20;

        $finish;
    end

endmodule