`timescale 1ns / 1ps

module sr_flip_flop(s, r, clk, q, nq);
    input s, r, clk;
    output q, nq;
    reg s_clk, r_clk;
    
    always @(posedge clk) begin
        s_clk <= s;
        r_clk <= r;
    end
    
    nor_sr_latch device(.s(s_clk), .r(r_clk), .q(q), .nq(nq));
endmodule
