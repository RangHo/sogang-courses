`timescale 1ns / 1ps

module d_latch(d, e, q, nq);
    input d, e;
    output q, nq;
    wire s, r;
    
    assign s = d & e;
    assign r = ~d & e;
    
    nor_sr_latch device(.s(s), .r(r), .q(q), .nq(nq));
endmodule
