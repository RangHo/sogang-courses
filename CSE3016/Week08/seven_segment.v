`timescale 1ns / 1ps

module seven_segment(a, b, c, d, A, B, C, D, E, F, G, seg);
   input  a, b, c, d;
   output A, B, C, D, E, F, G, seg;

   assign A = (b & c) | (~a & c) | (a & ~d) | (~b & ~d) | (~a & b & d) | (a & ~b & ~c);
   assign B = (~b & ~d) | (~b & ~c) | (~a & c & d) | (a & ~c & d) | (~a & ~c & ~d);
   assign C = (~c & d) | (~a & d) | (a & ~b) | (~a & b) | (~b & ~c);
   assign D = (~a &c & ~d) | (~b & c & d) | (b & ~c & d) | (a & b & ~d) | (~b & ~c & ~d);
   assign E = (c & ~d) | (a & c) | (a & b) | (~b & ~d);
   assign F = (a & c) | (a & ~b) | (b & ~d) | (~c & ~d) + (~a & b & ~c);
   assign G = (a & c) | (~b & c) | (a & ~b) | (b & ~c & d) | (~a & b & ~d);
   assign seg = 1;

endmodule
