`timescale 1ns / 1ps

module nor_sr_latch(s, r, q, nq);
    input s, r;
    output q, nq;
    
    nor(q, r, nq);
    nor(nq, s, q);
endmodule
