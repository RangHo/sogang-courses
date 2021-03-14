`timescale 1ns / 1ps

module three_input_and_gate_b_tb;

    reg a, b, c;
    wire d, e;
    
    three_input_and_gate_b DUT (
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .e(e)
    );
    
    initial begin
        a = 0;
        b = 0;
        c = 0;
        #20;
        
        a = 0;
        b = 0;
        c = 1;
        #20;
        
        a = 0;
        b = 1;
        c = 0;
        #20;
        
        a = 0;
        b = 1;
        c = 1;
        #20;
        
        a = 1;
        b = 0;
        c = 0;
        #20;
        
        a = 1;
        b = 0;
        c = 1;
        #20;
        
        a = 1;
        b = 1;
        c = 0;
        #20;
        
        a = 1;
        b = 1;
        c = 1;
        #20;
        
        $finish;
    end

endmodule
