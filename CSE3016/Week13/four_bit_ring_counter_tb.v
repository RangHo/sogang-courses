`timescale 1ns / 1ps

module four_bit_ring_counter_tb;
    reg clk;
    wire [3:0] out;

    four_bit_ring_counter DUT(clk, out);

    initial begin
        $dumpfile("four_bit_ring_counter.vcd");
        $dumpvars(0, four_bit_ring_counter_tb);

        clk = 0;
        #200 $finish;
    end

    always clk = #10 ~clk;

endmodule

