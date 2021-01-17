module calc(output [N-1: 0] out, input [N-1: 0] p_out, input [N-1: 0] x, input [N-1: 0] y, input wa, input wb, input clk, input m1, input m2);

    parameter N = 8;

    wire [N-1:0] r2sA;
    wire [N-1:0] s2rA;
    wire [N-1:0] r2sB;
    wire [N-1:0] s2rB;

    //STATO
    registro  #(N) A(r2sA, s2rA, clk, clk);
    registro  #(N) B(r2sB, s2rB, clk, clk);


    

endmodule