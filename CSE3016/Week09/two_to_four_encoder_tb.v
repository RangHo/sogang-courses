`timescale 1ns / 1ps

module two_to_four_encoder_tb;

    reg A, B, C, D;
    wire E0, E1;
    two_to_four_encoder DUT (
        .A(A),
        .B(B),
        .C(C),
        .D(D),
        .E0(E0),
        .E1(E1)
    );

    initial begin
        A = 0;
        B = 0;
        C = 0;
        D = 0;
        #20;

        A = 0;
        B = 0;
        C = 0;
        D = 1;
        #20;

        A = 0;
        B = 0;
        C = 1;
        D = 0;
        #20;

        A = 0;
        B = 0;
        C = 1;
        D = 1;
        #20;

        A = 0;
        B = 1;
        C = 0;
        D = 0;
        #20;

        A = 0;
        B = 1;
        C = 0;
        D = 1;
        #20;

        A = 0;
        B = 1;
        C = 1;
        D = 0;
        #20;

        A = 0;
        B = 1;
        C = 1;
        D = 1;
        #20;

        A = 1;
        B = 0;
        C = 0;
        D = 0;
        #20;

        A = 1;
        B = 0;
        C = 0;
        D = 1;
        #20;

        A = 1;
        B = 0;
        C = 1;
        D = 0;
        #20;

        A = 1;
        B = 0;
        C = 1;
        D = 1;
        #20;

        A = 1;
        B = 1;
        C = 0;
        D = 0;
        #20;

        A = 1;
        B = 1;
        C = 0;
        D = 1;
        #20;

        A = 1;
        B = 1;
        C = 1;
        D = 0;
        #20;

        A = 1;
        B = 1;
        C = 1;
        D = 1;
        #20;

        $finish;
    end

endmodule