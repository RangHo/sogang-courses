`timesclae 1ns / 1ps

module four_to_two_and_decoder(A, B, D0, D1, D2, D3);
    input A, B;
    output D0, D1, D2, D3;

    assign D0 = ~A & ~B;
    assign D1 = ~A & B;
    assign D2 = A & ~B;
    assign D3 = A & B;
endmodule
