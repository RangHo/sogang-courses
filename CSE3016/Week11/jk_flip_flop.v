`timescale 1ns / 1ps

module jk_flip_flop(j, k, clk, q, nq);
    input j, k, clk;
    output q, nq;
    reg s, r;
    
    always @(posedge clk) begin
        s <= j & nq;
        r <= k & q;
    end
    
    nor_sr_latch device(.s(s), .r(r), .q(q), .nq(nq));
endmodule

