`timescale 1ns / 1ps

module jk_flip_flop(j, k, clk, rst, q, nq);
    input j, k, clk, rst;
    output q, nq;
    reg s, r;
    
    initial begin
        s = 0;
        r = 1;
    end
    
    always @(posedge clk) begin
        if (rst) begin
            s <= 0;
            r <= 1;
        end
        else begin
            s <= j & nq;
            r <= k & q;
        end
    end
    
    nor_sr_latch device(.s(s), .r(r), .q(q), .nq(nq));
endmodule
