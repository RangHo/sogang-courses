`timescale 1ns / 1ps

module four_input_nor_gate_a_tb;

    reg a, b, c, d;
    wire e;
    four_input_nor_gate_a DUT (
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