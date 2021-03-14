`timescale 1ns / 1ps

module odd_parity_generator_tb;

    reg a, b, c, d;
    wire e;
    odd_parity_generator DUT (
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .e(e)
    );

    initial begin
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        #20;

        a = 0;
        b = 0;
        c = 0;
        d = 1;
        #20;

        a = 0;
        b = 0;
        c = 1;
        d = 0;
        #20;

        a = 0;
        b = 0;
        c = 1;
        d = 1;
        #20;

        a = 0;
        b = 1;
        c = 0;
        d = 0;
        #20;

        a = 0;
        b = 1;
        c = 0;
        d = 1;
        #20;

        a = 0;
        b = 1;
        c = 1;
        d = 0;
        #20;

        a = 0;
        b = 1;
        c = 1;
        d = 1;
        #20;

        a = 1;
        b = 0;
        c = 0;
        d = 0;
        #20;

        a = 1;
        b = 0;
        c = 0;
        d = 1;
        #20;

        a = 1;
        b = 0;
        c = 1;
        d = 0;
        #20;

        a = 1;
        b = 0;
        c = 1;
        d = 1;
        #20;

        a = 1;
        b = 1;
        c = 0;
        d = 0;
        #20;

        a = 1;
        b = 1;
        c = 0;
        d = 1;
        #20;

        a = 1;
        b = 1;
        c = 1;
        d = 0;
        #20;

        a = 1;
        b = 1;
        c = 1;
        d = 1;
        #20;

        $finish;
    end

endmodule