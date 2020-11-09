`timescale 1ns / 1ps

module nand_sr_latch(s, r, q, nq);
    input s, r;
    output q, nq;
    
    nand(q, s, nq);
    nand(nq, r, q);
    
endmodule
