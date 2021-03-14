`timescale 1ns / 1ps

module eight_to_one_mux_tb;

    reg S0, S1, S2;
    wire I0, I1, I2, I3, I4, I5, I6, I7, O;
    eight_to_one_mux DUT (
        .S0(S0),
        .S1(S1),
        .S2(S2),
        .I0(I0),
        .I1(I1),
        .I2(I2),
        .I3(I3),
        .I4(I4),
        .I5(I5),
        .I6(I6),
        .I7(I7),
        .O(O)
    );

    initial begin
        S0 = 0;
        S1 = 0;
        S2 = 0;
        #20;

        S0 = 0;
        S1 = 0;
        S2 = 1;
        #20;

        S0 = 0;
        S1 = 1;
        S2 = 0;
        #20;

        S0 = 0;
        S1 = 1;
        S2 = 1;
        #20;

        S0 = 1;
        S1 = 0;
        S2 = 0;
        #20;

        S0 = 1;
        S1 = 0;
        S2 = 1;
        #20;

        S0 = 1;
        S1 = 1;
        S2 = 0;
        #20;

        S0 = 1;
        S1 = 1;
        S2 = 1;
        #20;

        $finish;
    end

endmodule