`timescale 1ns / 1ps

module d_flip_flop(d, clk, q, nq);
    input d, clk;
    output q, nq;
    reg d_clk;
    
    always @(posedge clk) begin
        d_clk <= d;
    end
    
    d_latch device(.d(d_clk), .e(1), .q(q), .nq(nq));
endmodule
