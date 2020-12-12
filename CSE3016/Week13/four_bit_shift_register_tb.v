`timescale 1ns / 1ps

module four_bit_shift_register_tb;
    reg clk, in;
    wire [3:0] out;

    four_bit_shift_register DUT(clk, in, out);

    initial begin
        $dumpfile("four_bit_shift_register.vcd");
        $dumpvars(1, four_bit_shift_register_tb);

        clk = 0;
        in = 1;

        #35 in = 0;

        #20 in = 1;

        #40 in = 0;

        #200 $finish;
    end

    always clk = #10 ~clk;

endmodule

