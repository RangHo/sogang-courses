`timescale 1ns / 1ps

module four_to_two_nand_decoder_tb;

    reg A, B;
    wire D0, D1, D2, D3;
    four_to_two_nand_decoder DUT (
        .A(A),
        .B(B),
        .D0(D0),
        .D1(D1),
        .D2(D2),
        .D3(D3)
    );

    initial begin
        A = 0;
        B = 0;
        #20;

        A = 0;
        B = 1;
        #20;

        A = 1;
        B = 0;
        #20;

        A = 1;
        B = 1;
        #20;

        $finish;
    end

endmodule