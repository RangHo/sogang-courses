`timescale 1ns / 1ps

module eight_to_one_mux(S0, S1, S2, I0, I1, I2, I3, I4, I5, I6, I7, O);
    input S0, S1, S2;
    output I0, I1, I2, I3, I4, I5, I6, I7, O;

    assign I0 = 0;
    assign I1 = 1;
    assign I2 = 0;
    assign I3 = 1;
    assign I4 = 0;
    assign I5 = 1;
    assign I6 = 0;
    assign I7 = 1;
    assign O = (~S0 & ~S1 & ~S2 & I0) |  (~S0 & ~S1 & S2 & I1) | (~S0 & S1 & ~S2 & I2) | (~S0 & S1 & S2 & I3) | (S0 & ~S1 & ~S2 & I4) | (S0 & ~S1 & S2 & I5) | (S0 & S1 & ~S2 & I6) | (S0 & S1 & S2 & I7);
endmodule
