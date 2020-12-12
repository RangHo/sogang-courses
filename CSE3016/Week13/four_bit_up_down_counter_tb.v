`timescale 1ns / 1ps

module four_bit_up_down_counter_tb;
    reg clk, rst, down;
    wire [3:0] out;

    four_bit_up_down_counter DUT(clk, rst, down, out);

    initial begin
        $dumpfile("four_bit_up_down_counter.vcd");
        $dumpvars(1, four_bit_up_down_counter_tb);

        clk = 0;
        down = 0;
        rst = 0;

        // Count up for 20 cycles and set the down flag
        #400 down = ~down;

        // After 20 more cycles, pull reset pin high
        #400 rst = ~rst;

        #40 $finish;
    end

    always clk = #10 ~clk;

endmodule
