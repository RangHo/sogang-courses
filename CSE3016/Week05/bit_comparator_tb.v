`timescale 1ns / 1ps

module bit_comparator_tb;

    reg a, b;
    wire c, d, e, f;
    bit_comparator DUT (
        .a(a),
        .b(b),
        .eq(c),
        .neq(d),
        .gt(e),
        .lt(f)
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