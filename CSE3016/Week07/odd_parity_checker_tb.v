`timescale 1ns / 1ps

module odd_parity_checker_tb;

    reg a, b, c, d, p;
    wire pec;
    odd_parity_checker DUT (
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .p(p),
        .pec(pec)
    );

    initial begin
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        p = 0;
        #20;

        a = 0;
        b = 0;
        c = 0;
        d = 0;
        p = 1;
        #20;

        a = 0;
        b = 0;
        c = 0;
        d = 1;
        p = 0;
        #20;

        a = 0;
        b = 0;
        c = 0;
        d = 1;
        p = 1;
        #20;

        a = 0;
        b = 0;
        c = 1;
        d = 0;
        p = 0;
        #20;

        a = 0;
        b = 0;
        c = 1;
        d = 0;
        p = 1;
        #20;

        a = 0;
        b = 0;
        c = 1;
        d = 1;
        p = 0;
        #20;

        a = 0;
        b = 0;
        c = 1;
        d = 1;
        p = 1;
        #20;

        a = 0;
        b = 1;
        c = 0;
        d = 0;
        p = 0;
        #20;

        a = 0;
        b = 1;
        c = 0;
        d = 0;
        p = 1;
        #20;

        a = 0;
        b = 1;
        c = 0;
        d = 1;
        p = 0;
        #20;

        a = 0;
        b = 1;
        c = 0;
        d = 1;
        p = 1;
        #20;

        a = 0;
        b = 1;
        c = 1;
        d = 0;
        p = 0;
        #20;

        a = 0;
        b = 1;
        c = 1;
        d = 0;
        p = 1;
        #20;

        a = 0;
        b = 1;
        c = 1;
        d = 1;
        p = 0;
        #20;

        a = 0;
        b = 1;
        c = 1;
        d = 1;
        p = 1;
        #20;

        a = 1;
        b = 0;
        c = 0;
        d = 0;
        p = 0;
        #20;

        a = 1;
        b = 0;
        c = 0;
        d = 0;
        p = 1;
        #20;

        a = 1;
        b = 0;
        c = 0;
        d = 1;
        p = 0;
        #20;

        a = 1;
        b = 0;
        c = 0;
        d = 1;
        p = 1;
        #20;

        a = 1;
        b = 0;
        c = 1;
        d = 0;
        p = 0;
        #20;

        a = 1;
        b = 0;
        c = 1;
        d = 0;
        p = 1;
        #20;

        a = 1;
        b = 0;
        c = 1;
        d = 1;
        p = 0;
        #20;

        a = 1;
        b = 0;
        c = 1;
        d = 1;
        p = 1;
        #20;

        a = 1;
        b = 1;
        c = 0;
        d = 0;
        p = 0;
        #20;

        a = 1;
        b = 1;
        c = 0;
        d = 0;
        p = 1;
        #20;

        a = 1;
        b = 1;
        c = 0;
        d = 1;
        p = 0;
        #20;

        a = 1;
        b = 1;
        c = 0;
        d = 1;
        p = 1;
        #20;

        a = 1;
        b = 1;
        c = 1;
        d = 0;
        p = 0;
        #20;

        a = 1;
        b = 1;
        c = 1;
        d = 0;
        p = 1;
        #20;

        a = 1;
        b = 1;
        c = 1;
        d = 1;
        p = 0;
        #20;

        a = 1;
        b = 1;
        c = 1;
        d = 1;
        p = 1;
        #20;

        $finish;
    end

endmodule