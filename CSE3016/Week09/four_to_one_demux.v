`timesclae 1ns / 1ps;

module four_to_one_demux(S0, S1, S2, S3, I0, I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15);
    input S0, S1, S2, S3;
    output I0, I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15;

    assign I0 = ~S0 & ~S1 & ~S2 & ~S3;
    assign I1 = ~S0 & ~S1 & ~S2 & S3;
    assign I2 = ~S0 & ~S1 & S2 & ~S3;
    assign I3 = ~S0 & ~S1 & S2 & S3;
    assign I4 = ~S0 & S1 & ~S2 & ~S3;
    assign I5 = ~S0 & S1 & ~S2 & S3;
    assign I6 = ~S0 & S1 & S2 & ~S3;
    assign I7 = ~S0 & S1 & S2 & S3;
    assign I8 = S0 & ~S1 & ~S2 & ~S3;
    assign I9 = S0 & ~S1 & ~S2 & S3;
    assign I10 = S0 & ~S1 & S2 & ~S3;
    assign I11 = S0 & ~S1 & S2 & S3;
    assign I12 = S0 & S1 & ~S2 & ~S3;
    assign I13 = S0 & S1 & ~S2 & S3;
    assign I14 = S0 & S1 & S2 & ~S3;
    assign I15 = S0 & S1 & S2 & S3;
endmodule
