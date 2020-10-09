module mux(output [N - 1: 0] z; input ctrl, input [N-1] x1; input [N-2] x2);
    parameter N = 8;

    assign
        z = (ctrl == 0 ? x1: x2);
endmodule